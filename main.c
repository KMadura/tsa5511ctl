// External includes
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "linux/i2c-dev.h"
#include <syslog.h>

// My includes
#include "daemonize.c"
#include "config.c"
#include "main.h"

/*
 * Validation functions
 */

bool checkRegex(regex_t* regex, char* text) {
    return regexec(regex, text, 0, NULL, 0) != REG_NOMATCH;
}

bool validateFrequencyString(char* freq) {
    regex_t regex;

    // Only frequencies within 65.0-108MHz are allowed by default,
    // however you can modify these regex strings as you wish

    // 65.0-69.9MHz
    if (regcomp(&regex, "^6[5-9].[0-9]$", REG_EXTENDED)) return false;
    if (checkRegex(&regex, freq)) return true;

    // 70.0-99.9MHz
    if (regcomp(&regex, "^[7-9][0-9].[0-9]$", REG_EXTENDED)) return false;
    if (checkRegex(&regex, freq)) return true;

    // 100.0-107.9MHz
    if (regcomp(&regex, "^10[0-7].[0-9]$", REG_EXTENDED)) return false;
    if (checkRegex(&regex, freq)) return true;

    // 108.0MHz (not that you should broadcast at 108.0)
    if (regcomp(&regex, "^108.0$", REG_EXTENDED)) return false;
    return true;
}

bool validateDeviceString(char* dstring) {
    regex_t regex;

    int reti = regcomp(&regex, "^\\/dev\\/i2c-[0-9]+$", REG_EXTENDED);
    if (reti) { // Regex doesn't compile
        return false;
    }

    reti = regexec(&regex, dstring, 0, NULL, 0);
    if (reti == REG_NOMATCH) { // Can't find any match
        return false;
    }

    return true;
}

/*
 * Convert currentFrequency from a string into long
 */

long frequencyConversion(char* freq) {
    size_t freq_l = strlen(freq);
    char* eptr;

    // We must drop the dot in a string
    if (freq_l == 4) {
        char newstring[3] = {freq[0], freq[1], freq[3]};
        return strtol(newstring, &eptr, 10) * 2;
    } else {
        char newstring[4] = {freq[0], freq[1], freq[2], freq[4]};
        return strtol(newstring, &eptr, 10) * 2;
    }
}

bool checkIfPowerOn() {
    char* data = malloc(1);
    data[0] = 0x60;

    return (read(device, data, 1) & 0b10000000) > 0;
}

/*
 * TSA5511 communication functions
 */

bool tsaInitialize() {
    char* data = malloc(2);
    data[0] = 0x00;
    data[1] = 0x10;

    return (write(device, data, 2) == 2);
}

bool tsaSetFrequency(long frequency) {
    char* data = malloc(2);
    data[0] = (frequency & 0xFF00) >> 8;
    data[1] = frequency & 0x00FF;

    return (write(device, data, 2) == 2);
}

bool initial_i2c_communication() {
    int address = 0x61;

    if (ioctl(device, I2C_SLAVE, address) < 0) {
        printf("Could not communicate with a device\n");
        return 0;
    }

    return 1;
}

void print_usage() {
    printf("Usage:\ntsa5511ctl set currentFrequency device\ntsa5511ctl get parameter device\ntsa5511ctl daemon device\n");
}

/*
 * Main logic
 */

int main(int argc, char** argv) {
    loadConfig();

    printf("Host: %s\n", configParams.host);
    printf("Port: %s\n", configParams.port);
    printf("Device: %s\n", configParams.device);

    if (argc != 4) {
        if (argc == 3 && strcmp(argv[1], "daemon") == 0) {

            device = open(argv[2], O_RDWR);
            if (device < 0) {
                printf("Could not open a device\n");
                return 1;
            }

            return mainDaemon();
        }

        print_usage();
        return 1;
    }

    if (strlen(argv[1]) != 3) {
        printf("Please use get or set command\n");
        return 1;
    }

    if (!validateDeviceString(argv[3])) {
        printf("Wrong i2c device name\n");
        return 1;
    }

    device = open(argv[3], O_RDWR);
    if (device < 0) {
        printf("Could not open a device\n");
        return 1;
    }

    if (strcmp(argv[1], "set") == 0) {
        return mainSet(argv[2]);
    }

    return mainGet(argv[2]);
}

int mainSet(char* frequencyString) {
    if (!initial_i2c_communication()) {
        printf("Could not communicate with a device\n");
        return 1;
    }

    if (!validateFrequencyString(frequencyString)) {
        printf("Only frequencies within 65.0-108.0 are allowed\n");
        return 1;
    }

    long frequency = frequencyConversion(frequencyString);
    if (frequency < 1300 || frequency > 2160) {
        printf("Only frequencies within 65.0-108.0 are allowed (2)\n");
        return 1;
    }

    if (!tsaInitialize()) {
        printf("Failed to initialize TSA5511\n");
        return 1;
    }

    usleep(10000); // 10ms

    if (!tsaSetFrequency(frequency)) {
        printf("Failed to set TSA5511 currentFrequency\n");
        return 1;
    }

    printf("Frequency is set\n");

    return 0;
}

int mainGet(char* optionString) {
    if (!initial_i2c_communication()) {
        printf("Could not communicate with a device\n");
        return 1;
    }

    if (strcmp(optionString, "lock") == 0) {
        printf("TODO: Asking if PLL is locked\n");
        return 0;
    }

    printf("Please use one of available options:\n - lock\n - todo: others to implement\n");
    return 1;
}

int mainDaemon() {
    skeleton_daemon();
    if (initial_i2c_communication()) {
        printf("Could not communicate with a device\n");
        return 1;
    }

    while(1) {
        // TODO: Implement networking

        syslog( LOG_NOTICE, "rpiTsa5511Control is now running");
        sleep(20);
        //break;
    }

    syslog (LOG_NOTICE, "rpiTsa5511Control is terminated");
    closelog();

    return EXIT_SUCCESS;
}
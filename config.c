//
// Created by krzysiek on 22.02.2023.
//

#include "string.h"
#include "config.h"

int loadConfig() {
    // Default settings
    strcpy(configParams.host, defaultHost);
    strcpy(configParams.port, defaultPort);
    strcpy(configParams.device, defaultDevice);

    FILE* configFile = fopen(defaultConfigLocation, "r");

    if (configFile == NULL) {
        fputs("Failed to open configuration file! Using built in default settings.\n", stdout);
        return 0;
    }

    char line[1024];

    while (fgets(line, sizeof(line), configFile)) {
        if (line[0] == '#') {
            // Comments are ignored
            continue;
        }

        if (strlen(line) < 3) {
            // Empty or wrong lines are ignored
            continue;
        }

        // Removing trailing newline character
        line[strcspn(line, "\n")] = 0;

        if (strncmp("host: ", line, 6) == 0) {
            strncpy(configParams.host, line+6, strlen(line));
        } else
        if (strncmp("port: ", line, 6) == 0) {
            strncpy(configParams.port, line+6, strlen(line));
        } else
        if (strncmp("device: ", line, 8) == 0) {
            strncpy(configParams.device, line+8, strlen(line));
        }
    }

    fclose(configFile);
    return 1;
}
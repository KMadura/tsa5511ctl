#include <yaml.h>

char* defaultConfigLocation = "/etc/rpiTsa5511Control/config.yaml\0";
char* defaultPort = "555\0";
char* defaultHost = "localhost\0";

typedef struct ConfigParams {
    char* host;
    char* port;
};
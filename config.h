#include <yaml.h>

char defaultConfigLocation[] = "/etc/tsa5511ctl/default.cfg";
char defaultPort[] = "555";
char defaultHost[] = "localhost";
char defaultDevice[] = "/dev/i2c-1";

struct ConfigParams {
    char host[64];
    char port[64];
    char device[64];
} configParams;

int loadConfig();
//
// Created by krzysiek on 22.02.2023.
//

#include "config.h"

void getConfigParams() {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);

    FILE* configFile = fopen(defaultConfigLocation, "r");



}
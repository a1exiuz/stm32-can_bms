#ifndef CLI_H
#define CLI_H

#include<stdint.h>

typedef void (*CMD_Handler_t)(const char *args);

typedef struct {
    const char *name;
    CMD_Handler_t handler;
} Command_t;

extern const Command_t commands[];
extern const uint8_t NUM_CMDS;

void CLI_command_parser(const char *s);

void handle_ping(const char *args);

void handle_raw_to_voltage(const char *args);

void handle_calculate_cell_voltage(const char *args);

#endif //cli.h

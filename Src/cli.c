#include "cli.h"
#include "uart.h"
#include "bms.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const Command_t commands[] = {
    {"PING", handle_ping},
    {"RAW TO VOLTAGE", handle_raw_to_voltage},
	{"CALCULATE CELL VOLTAGE", handle_calculate_cell_voltage},
    {"AVG VOLTAGE", handle_avg_voltage},
    {"CALCULATE CHARGE", handle_calculate_charge},
    {"CHECK FAULT", handle_check_fault}
};

#define NUM_CMDS  (sizeof(commands) / sizeof(commands[0]))

void CLI_command_parser(const char *s) {
    if(!s) 
        return;

    for(uint8_t i = 0; i < NUM_CMDS; i++) {
    	if(strncmp(s, commands[i].name, strlen(commands[i].name)) == 0) {
    	    // extract args and everything after the command name and ':'
    	    const char *args = s + strlen(commands[i].name) + 1;
    	    commands[i].handler(args);
    	    return;
        }
    }
    UART_send_str("UNKNOWN COMMAND\r\n");
}

void handle_ping(const char *args) {
    (void)args; 
    UART_send_str("PONG\r\n");
}

void handle_raw_to_voltage(const char *args) {
    char buf1[64];
    strncpy(buf1, args, 64);

    char *token = strtok(buf1, ":");
    uint16_t raw = (uint16_t)atoi(token);

    token = strtok(NULL, ":");
    float r1 = (float)atof(token);

    token = strtok(NULL, ":");
    float r2 = (float)atof(token);

    float cell = BMS_raw_to_volt(raw, r1, r2);

    char buf[20];
    sprintf(buf, "%.2f\r\n", cell);
    UART_send_str("CELL VOLTAGE: ");
    UART_send_str(buf);
}

void handle_calculate_cell_voltage(const char *args) {
	char buf1[64];
    strncpy(buf1, args, 64);

    char *token = strtok(buf1, ":");
    uint16_t raw1 = (uint16_t)atoi(token);

    token = strtok(NULL, ":");
    uint16_t raw2 = (uint16_t)atoi(token);

    token = strtok(NULL, ":");
    uint16_t raw3 = (uint16_t)atoi(token);

    token = strtok(NULL, ":");
    uint16_t raw4 = (uint16_t)atoi(token);

    uint16_t raw[4] = {
        raw1, raw2, raw3, raw4
    };

    float voltages[4] = {0};

    BMS_calculate_cell_voltage(raw, voltages, 4);
    char buf[20];

    for(uint8_t i = 0; i < 4; i++) {
        UART_send_str("CELL ");
        UART_print_int(i + 1);
        UART_send_str(": ");
        sprintf(buf, "%.2f\r\n", voltages[i]);
        UART_send_str(buf);
    }

}

void handle_avg_voltage(const char *args) {
    (void)args;
    UART_send_str("AVG VOLTAGE ENABLED\r\n");
}

void handle_calculate_charge(const char *args) {
    (void)args;
    UART_send_str("CALCULATING CHARGE\r\n");
}

void handle_check_fault(const char *args) {
    (void)args;
    UART_send_str("CHECKING FAULT\r\n");
}
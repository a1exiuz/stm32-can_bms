#include "cli.h"
#include "uart.h"
#include "bms.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const Command_t commands[] = {
    {"PING", handle_ping},
    {"RAW TO VOLTAGE", handle_raw_to_voltage},
	{"CALCULATE CELL VOLTAGE", handle_calculate_cell_voltage}
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

    UART_send_str("RAW_TO_VOLT ENABLED\r\n");
    
    UART_send_str("args: ");
    UART_send_str(args);
    UART_send_str("\r\n");

    char buf1[64];
    strncpy(buf1, args, 64);

    char *token = strtok(buf1, ":");
    UART_send_str("token1: ");
    UART_send_str(token);
    UART_send_str("\r\n");
    uint16_t raw = (uint16_t)atoi(token);

    token = strtok(NULL, ":");
    UART_send_str("token2: ");
    UART_send_str(token);
    UART_send_str("\r\n");
    float r1 = (float)atof(token);

    token = strtok(NULL, ":");
    UART_send_str("token3: ");
    UART_send_str(token);
    UART_send_str("\r\n");
    float r2 = (float)atof(token);

    float cell = BMS_raw_to_volt(raw, r1, r2);

    char buf[20];
    sprintf(buf, "%.2f\r\n", cell);
    UART_send_str("CELL VOLTAGE: ");
    UART_send_str(buf);
}

void handle_calculate_cell_voltage(const char *args) {
	(void)args;
	UART_send_str("CELL TO VOLTAGE\r\n");
}


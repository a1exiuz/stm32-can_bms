#include "cli.h"
#include "uart.h"

const Command_t commands[] = {
    {"PING", handle_ping}

};

#define NUM_CMDS  (sizeof(commands) / sizeof(commands[0]))

void CLI_command_parser(const char *s) {
    for(uint8_t i = 0; i < NUM_CMDS; i++) {
        if(strcmp(s, commands[i].name) == 0) {
            commands[i].handler(s);
            return;
        }
    }
    UART_send_str("UNKNOWN COMMAND\r\n");
}

void handle_ping(const char *args) {
    (void)args; 
    UART_send_str("PONG\r\n");
}

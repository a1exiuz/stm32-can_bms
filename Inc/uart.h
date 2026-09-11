#ifndef UART_H
#define UART_H

#include <stdint.h>

#define USART2 ((USART_RegMap_t*)0x40004400UL)

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_RegMap_t;

void UART_init(void);

void UART_send_char(char c);

void UART_send_str(const char *s);;

void UART_print_int(int32_t val);


#endif //uart.h
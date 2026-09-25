#include "uart.h"
#include "rcc.h"
#include "gpio.h"
#include "cli.h"

void UART_init(void){
    GPIO_Config_t TX = {
        .port = GPIOA,
        .pin = 2,
        .port_code = 0,
        .mode = AF,
        .type = PUSH_PULL,
        .speed = HIGH,
        .pull = NO_PULL,
        .af = 7
    };

    GPIO_Config_t RX = {
        .port = GPIOA,
        .pin = 3,
        .port_code = 0,
        .mode = AF,
        .type = PUSH_PULL,
        .speed = HIGH,
        .pull = PULL_UP,
        .af = 7
    };

    GPIO_init(&TX);
    GPIO_init(&RX);


    RCC->APB1ENR |= (1U << 17);

    USART2->CR1 |= (1U << 13);
    USART2->CR1 &= ~(1U << 12);
    USART2->CR2 &= ~(3U << 12);
    USART2->BRR = (8 << 4) | (11);
    USART2->CR1 |= (1U << 3);
    USART2->CR1 |= (1U << 2);
}

void UART_send_char(char c) {
    while(!(USART2->SR & (1U << 7)));
    USART2->DR = (uint8_t)c;
}

char UART_receive_char(void) {
    while(!(USART2->SR & (1U << 5))); //wait till rnxe set
    return((char)USART2->DR);         //read  to the DR register to clear RNXE
}

void UART_send_str(const char *c) {
    while(*c != '\0') {
        UART_send_char(*c);
        c++;
    } 
}

void UART_receive_str(char *buf, uint8_t max_len) {
    char c;
    uint8_t idx = 0;
    
    while(idx < max_len - 1) {
       c = UART_receive_char();
       if(c == '\n' || c == '\r') break;
       buf[idx] = c;
       idx++;
    }
    buf[idx] = '\0'; 
}

void UART_print_int(int32_t val) {
    char buf[10];
    uint8_t idx = 0;

    if(val == 0) {
        UART_send_char('0');
        return;
    } else if(val < 0) {
        UART_send_char('-');
        val = -val;
    }

    while(val > 0){
        buf[idx] = (char)val % 10;
        idx++;
        val /= 10;
    }

    for(int8_t i = (int8_t)(idx - 1); i >= 0; i--){
        UART_send_char('0' + buf[i]);
    }
}


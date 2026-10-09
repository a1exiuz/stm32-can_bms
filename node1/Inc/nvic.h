#ifndef NVIC_H
#define NVIC_H

#include <stdint.h>

#define NVIC_ISER0 (*(volatile uint32_t *)0xE000E100UL)
#define NVIC_ISER1 (*(volatile uint32_t *)0xE000E104UL)
#define NVIC_ICER0 (*(volatile uint32_t *)0xE000E180UL)
#define NVIC_ICER1 (*(volatile uint32_t *)0xE000E184UL)
#define NVIC_IPR ((volatile uint8_t *)0xE000E400UL)

typedef enum {
    USART2_IRQn = 38
} IRQn_t;

void NVIC_enable(uint8_t irq, uint8_t priority);

void NVIC_disable(uint8_t irq);

#endif //nvic.h
#include "nvic.h"
#include "stdint.h"

void NVIC_enable(uint8_t irq, uint8_t priority) {
    NVIC_IPR[irq] = priority << 4;

    if(irq < 32)
        NVIC_ISER0 |= (1U << irq);
    else
        NVIC_ISER1 |= (1U << (irq - 32));
}

void NVIC_disable(uint8_t irq) {
    if(irq < 32)
        NVIC_ICER0 |= (1U << irq);
    else   
        NVIC_ICER1 |= (1U << (irq - 32));
}
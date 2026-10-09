#include "exti.h"
#include "rcc.h"
#include "nvic.h"
#include <stdint.h>

void EXTI_init(EXTI_Config_t *cfg) {
    if(!cfg)
        return;

    RCC->APB2ENR |= (1U << 14);

    SYSCFG->EXTICR[cfg->pin / 4] &= ~(0xFU <<((cfg->pin % 4) * 4));
    SYSCFG->EXTICR[cfg->pin / 4] |= (cfg->port_code << ((cfg->pin % 4) * 4));

    EXTI->PR |= (1U << cfg->pin);
    EXTI->IMR |= (1U << cfg->pin);

    if(cfg->trigger == BOTH) {
        EXTI->RTSR |= (1U << cfg->pin);
        EXTI->FTSR |= (1U << cfg->pin);
    } 
    else if(cfg->trigger == RISING) 
        EXTI->RTSR |= (1U << cfg->pin);
    else if(cfg->trigger == FALLING)
        EXTI->FTSR |= (1U << cfg->pin);

    if(cfg->pin <= 4) 
        NVIC_enable(cfg->pin + 5, cfg->priority);
    else if (cfg->pin <= 9)
        NVIC_enable(EXTI9_5_IRQn, cfg->priority);
    else
        NVIC_enable(EXTI15_10_IRQn, cfg->priority);
}

//handlers missing 
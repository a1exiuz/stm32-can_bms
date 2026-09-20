#include "adc.h"
#include "rcc.h"
#include "gpio.h"
#include <stdint.h>

void ADC_init(void) {
    GPIO_Config_t cell_1 = {
        .port = GPIOA,
        .pin = 0,
        .port_code = 0,

        .mode = ANALOG,
        .type = PUSH_PULL, // IGNORED
        .speed = LOW,      // IGNORED
        .pull = NO_PULL,
        .af = 0            // IGNORED
    };

    GPIO_Config_t cell_2 = {
        .port = GPIOA,
        .pin = 1,
        .port_code = 0,

        .mode = ANALOG,
        .type = PUSH_PULL, // IGNORED
        .speed = LOW,      // IGNORED
        .pull = NO_PULL,
        .af = 0            // IGNORED
    };

    GPIO_Config_t cell_3 = {
        .port = GPIOA,
        .pin = 4,
        .port_code = 0,

        .mode = ANALOG,
        .type = PUSH_PULL, // IGNORED
        .speed = LOW,      // IGNORED
        .pull = NO_PULL,
        .af = 0            // IGNORED
    };

    GPIO_Config_t cell_4 = {
        .port = GPIOA,
        .pin = 6,
        .port_code = 0,

        .mode = ANALOG,
        .type = PUSH_PULL, // IGNORED
        .speed = LOW,      // IGNORED
        .pull = NO_PULL,
        .af = 0            // IGNORED
    };

    GPIO_init(&cell_1);
    GPIO_init(&cell_2);
    GPIO_init(&cell_3);
    GPIO_init(&cell_4);

    RCC->APB2ENR |= (1U << 8);
    ADC_COMMON->CCR &= ~(3U << 16);
    ADC_COMMON->CCR |= (1U << 16);
    ADC1->CR2 |= (1U << 0);
}

uint16_t ADC_single_conversion(uint8_t channel) {

    if(channel >= 10) {
        ADC1->SMPR1 &= ~(7U << ((channel -10) * 3));
        ADC1->SMPR1 |= (7U << ((channel - 10) * 3));
    } else {
        ADC1->SMPR2 &= ~(7U << ((channel) * 3));
        ADC1->SMPR2 |= (7U << ((channel) * 3));
    }
    
    ADC1->SQR3 &= ~(0x1FU);
    ADC1->SQR3 |= (channel);

    ADC1->SR &= ~(1U << 1);
    ADC1->CR2 |= (1U << 30);

    while(!(ADC1->SR & (1U << 1)));

    return((uint16_t)ADC1->DR);
}

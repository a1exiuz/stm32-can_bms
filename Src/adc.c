#include "adc.h"
#include "rcc.h"
#include "gpio.h"
#include <stdint.h>

void ADC_init(ADC_Config_t *cfg) {
    //wait on ADC pins 
    if(!cfg)
        return;


    RCC->APB2ENR |= (1U << 8);
    
    ADC_COMMON->CCR &= ~(3U << 16);
    ADC_COMMON->CCR |= (1U << 16);

    if(cfg->channel >= 10) {
        ADC1->SMPR1 &= ~(7U << ((cfg->channel -10) * 3));
        ADC1->SMPR1 |= (7U << ((cfg->channel - 10) * 3));
    } else {
        ADC1->SMPR2 &= ~(7U << ((cfg->channel) * 3));
        ADC1->SMPR2 |= (7U << ((cfg->channel) * 3));
    }

    ADC1->SQR1 &= ~(0xFU << 20);
    ADC1->SQR1 |= (3U << 20);

    ADC1->SQR3 &= ~(0x1FU << ((cfg->sequence_pos - 1) * 5));
    ADC1->SQR3 |= (cfg->channel << ((cfg->sequence_pos - 1) * 5));

    ADC1->CR2 |= (1U << 0);
}

uint16_t ADC_single_conversion(void) {
    ADC1->CR2 |= (1U << 30);
    while(!(ADC1->SR & (1U << 1)));

    return((uint16_t)ADC1->DR);
}
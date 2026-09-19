#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#define ADC1 ((ADC_RegMap_t*)0x40012000UL)
#define ADC_COMMON ((ADC_Common_RegMap_t*)0x40012300UL)

typedef struct {
    uint8_t channel;
    uint8_t conversions;
    uint8_t sampling;
    uint8_t sequence_pos;
} ADC_Config_t;

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMPR1;
    volatile uint32_t SMPR2;
    volatile uint32_t JOFR1;
    volatile uint32_t JOFR2;
    volatile uint32_t JOFR3;
    volatile uint32_t JOFR4;
    volatile uint32_t HTR;
    volatile uint32_t LTR;
    volatile uint32_t SQR1;
    volatile uint32_t SQR2;
    volatile uint32_t SQR3;
    volatile uint32_t JSQR;
    volatile uint32_t JDR1;
    volatile uint32_t JDR2;
    volatile uint32_t JDR3;
    volatile uint32_t JDR4;
    volatile uint32_t DR;
} ADC_RegMap_t;

typedef struct {
    volatile uint32_t CSR;
    volatile uint32_t CCR;
    volatile uint32_t CDR;
} ADC_Common_RegMap_t;

void ADC_init(ADC_Config_t *cfg);

uint16_t ADC_single_conversion(uint8_t channel);

#endif 
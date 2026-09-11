#ifndef RCC_H
#define RCC_H

#include <stdint.h>

#define RCC ((RCC_RegMap_t*)0x40023800UL)

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1;
    volatile uint32_t AHB2;
    volatile uint32_t AHB3;
    volatile uint32_t RESERVED0;
    volatile uint32_t APB1;
    volatile uint32_t APB2;
    volatile uint32_t RESERVED1;
    volatile uint32_t RESERVED2;
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t RESERVED3;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t RESERVED4;
    volatile uint32_t RESERVED5;
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    volatile uint32_t RESERVED6;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t RESERVED7;
    volatile uint32_t RESERVED8;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t RESERVED9;
    volatile uint32_t RESERVED10;
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2;
    volatile uint32_t PLLSAI;
    volatile uint32_t DCKCFGR;
    volatile uint32_t CK;
    volatile uint32_t DCKCFGR2;
} RCC_RegMap_t;

#endif //rcc.h
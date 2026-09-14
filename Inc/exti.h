#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>

#define EXTI ((EXTI_RegMap_t*)0x40013C00UL)
#define SYSCFG ((SYSCFG_RegMap_t*)0x40013800UL)

#define EXTI0_IRQn     6
#define EXTI1_IRQn     7
#define EXTI2_IRQn     8
#define EXTI3_IRQn     9
#define EXTI4_IRQn     10
#define EXTI9_5_IRQn   23
#define EXTI15_10_IRQn 40

typedef struct {
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_RegMap_t;

typedef struct {
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];
    volatile uint32_t CMPCR;
    volatile uint32_t CFGR;
} SYSCFG_RegMap_t;

typedef enum {
    RISING = 0,
    FALLING,
    BOTH
} EXTI_Trigger_t;

typedef struct {
    uint8_t pin;
    uint8_t port_code;
    uint8_t priority;
    EXTI_Trigger_t trigger;
} EXTI_Config_t;

void EXTI_init(EXTI_Config_t *cfg);


#endif


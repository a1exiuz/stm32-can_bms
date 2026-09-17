#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define GPIOA ((GPIO_RegMap_t*)0x40020000UL)
#define GPIOB ((GPIO_RegMap_t*)0x40020400UL)
#define GPIOC ((GPIO_RegMap_t*)0x40020800UL)

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_RegMap_t;

typedef enum {
    INPUT = 0,
    OUTPUT,
    AF,
    ANALOG
} GPIO_Moder_t;

typedef enum {
    PUSH_PULL = 0,
    OPEN_DRAIN
} GPIO_Typer_t;

typedef enum {
    LOW = 0,
    MEDIUM,
    FAST,
    HIGH
} GPIO_Speedr_t;

typedef enum {
    NO_PULL = 0,
    PULL_UP,
    PULL_DOWN,
    RESERVED
} GPIO_Pull_t;


typedef struct {
    GPIO_RegMap_t *port;
    uint8_t pin;
    uint8_t port_code;

    GPIO_Moder_t mode;
    GPIO_Typer_t type;
    GPIO_Speedr_t speed;
    GPIO_Pull_t pull;
    uint8_t af;
} GPIO_Config_t;

void GPIO_init(const GPIO_Config_t *cfg);

#endif //gpio.h

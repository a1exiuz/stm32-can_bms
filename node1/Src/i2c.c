#include "i2c.h"
#include "gpio.h"
#include "rcc.h" 

void I2C_init(void) {
    GPIO_Config_t scl = {
        .port = GPIOB,
        .pin = 8,
        .port_code = 1,

        .mode = AF,
        .type = OPEN_DRAIN,
        .speed = HIGH,
        .pull = NO_PULL,
        .af = 4
    };

    GPIO_Config_t sda = {
        .port = GPIOB,
        .pin = 9,
        .port_code = 1,

        .mode = AF,
        .type = OPEN_DRAIN,
        .speed = HIGH,
        .pull = NO_PULL,
        .af = 4
    };

    GPIO_init(&scl);
    GPIO_init(&sda);

    RCC->APB1ENR |= (1U << 21);

    I2C1->CR1 |= (1U << 15);
    I2C1->CR1 &= ~(1U << 15);

    I2C1->CR2 |= 16;
    I2C1->CCR &= ~(0xFFFUL);
    I2C1->CCR |= 80;
    I2C1->TRISE = 17;

    I2C1->CR1 |= (1U << 0);
}

void I2C_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data) {
    while(I2C1->SR2 & (1U << 1));

    I2C1->CR1 |= (1U << 8);
    while(!(I2C1->SR1 & 1U));

    I2C1->DR = (dev_addr << 1);
    while(!(I2C1->SR1 & (1U << 1)));
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    while(!(I2C1->SR1 & (1U << 7)));
    I2C1->DR = reg_addr;

    while(!(I2C1->SR1 & (1U << 7)));
    I2C1->DR = data;

    while(!(I2C1->SR1 & (1U << 2)));
    I2C1->CR1 |= (1U << 9);
}

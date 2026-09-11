#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define I2C1 ((I2C_RegMap_t*)0x40005400)

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
    volatile uint32_t FLTR;
} I2C_RegMap_t;

void I2C_init(void);

void I2C_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);

#endif //i2c.h
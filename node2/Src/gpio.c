#include "gpio.h"
#include "rcc.h"
#include <stdint.h>

void GPIO_init(const GPIO_Config_t *cfg) {
    if(!cfg){
         return;
    }

    RCC->AHB1ENR |= (1U << cfg->port_code);

    cfg->port->MODER &= ~(3U << (cfg->pin * 2));
    cfg->port->MODER |= (cfg->mode << (cfg->pin * 2));

    if(cfg->mode == AF) {
        if(cfg->pin <= 7) {
            cfg->port->AFR[0] &= ~((uint32_t)0xF << ((cfg->pin) * 4));
            cfg->port->AFR[0] |= ((uint32_t)cfg->af << ((cfg->pin) * 4));
        } else {
            cfg->port->AFR[1] &= ~((uint32_t)0xF << ((cfg->pin % 8) * 4));
            cfg->port->AFR[1] |= ((uint32_t)cfg->af << ((cfg->pin % 8) * 4));
        }
    }

    cfg->port->OTYPER &= ~(1U << cfg->pin);
    cfg->port->OTYPER |= (cfg->type << cfg->pin);

    cfg->port->OSPEEDR &= ~(3U << (cfg->pin * 2));
    cfg->port->OSPEEDR |= (cfg->speed << (cfg->pin * 2)); 

    cfg->port->PUPDR &= ~(3U << (cfg->pin * 2));
    cfg->port->PUPDR |= (cfg->pull << (cfg->pin * 2));
}

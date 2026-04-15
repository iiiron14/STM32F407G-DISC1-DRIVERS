#ifndef SPI_H__
#define SPI_H__

#include "stm32f4xx.h"
#include <stdint.h>

void spi_gpio_init(void);
void spi1_config(void);
void sp1_trasmit(uint8_t *, uint32_t);
void sp1_receive(uint8_t *, uint32_t);
void cs_enable(void);
void cs_disable(void);

#endif

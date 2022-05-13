
#ifndef __FSMC_H__
#define __FSMC_H__

#include "gd32f30x.h"

#define FPGA_COMM_ADDRESS ((uint32_t)0x60000000)

extern void exmc_gpio_init();
extern void exmc_init();
extern void write_data(uint8_t address, uint16_t data);
extern uint8_t read_data(uint8_t address);

#endif

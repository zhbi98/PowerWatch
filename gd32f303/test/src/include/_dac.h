
#ifndef ___DAC_H__
#define ___DAC_H__

#include "gd32f30x.h"

#define _DAC_OUT_VAL      (0x7FF0)

#define _DAC              DAC0
#define _DAC_CLOCK        RCU_DAC

#define _DAC_CHANEL_GPIO  GPIOB
#define _DAC_CHANEL_PIN   GPIO_PIN_11
#define _DAC_CHANEL_CLOCK RCU_GPIOB

extern void _dac_gpio_init();
extern void _dac_init();

extern void _dac_put(unsigned int dacv);

#endif

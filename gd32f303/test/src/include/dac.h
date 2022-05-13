
#ifndef __DAC_H__
#define __DAC_H__

#include "gd32f30x.h"

#define DAC_OUT_VAL      (0x7FF0)

#define DAC              DAC0
#define DAC_CLOCK        RCU_DAC

#define DAC_CHANEL_GPIO  GPIOB
#define DAC_CHANEL_PIN   GPIO_PIN_11
#define DAC_CHANEL_CLOCK RCU_GPIOB

extern void dac_gpio_init();
extern void dac_init();

extern void dac_put(unsigned int dacv);

#endif

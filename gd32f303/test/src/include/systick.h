
#ifndef __SYS_TICK_H__
#define __SYS_TICK_H__

#include <stdint.h>
#include "gd32f30x.h"

#include "led.h"

static uint32_t sleep_t;

extern void systick_config();
extern void delay_1ms(uint32_t ms);
extern void SysTick_Handler();

#endif

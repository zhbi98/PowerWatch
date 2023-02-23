
#ifndef __TEMP_H__
#define __TEMP_H__

#include "gd32f10x.h"
#include "time.h"

#define TEMP_ADC       ADC0
#define TEMP_ADC_CLOCK RCU_ADC0

extern void inside_temp_adc_rcu_init();
extern void inside_temp_adc_init();
extern unsigned int read_inside_temp();

#endif

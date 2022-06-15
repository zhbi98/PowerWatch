
#ifndef __TEMP_SONSOR_H__
#define __TEMP_SONSOR_H__

#include "gd32f10x.h"
#include "time.h"

#define CURRENT_ADC ADC0
#define ADC_CLOCK   RCU_ADC0

extern void temp_adc_rcu_config();
extern void temp_adc_config();
extern int read_temp();

#endif

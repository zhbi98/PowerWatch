
#ifndef ___PWM_H__
#define ___PWM_H__

#include "gd32f30x.h"

/**
 * How to use:
 * int main()
 * {
 * 	pwm_init();
 * 
 * 	while (1);
 * }
 */

#define _TIMER       TIMER1
#define _TIMER_CLOCK RCU_TIMER1
#define _TIMER_CH    TIMER_CH_3

#define _PWM_GPIO    GPIOB
#define _PWM_PIN     GPIO_PIN_11
#define _PWM_CLOCK   RCU_GPIOB

extern void _pwm_gpio_init();
extern void _timers_init();
extern void _pwm_init();

extern void _pwm_out(unsigned int pwmv);

#endif

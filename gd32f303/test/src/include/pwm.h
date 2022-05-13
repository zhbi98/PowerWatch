
#ifndef __PWM_H__
#define __PWM_H__

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

#define TIMER       TIMER1
#define TIMER_CLOCK RCU_TIMER1
#define TIMER_CH    TIMER_CH_3

#define PWM_GPIO    GPIOB
#define PWM_PIN     GPIO_PIN_11
#define PWM_CLOCK   RCU_GPIOB

extern void pwm_gpio_init();
extern void timers_init();
extern void pwm_init();

extern void pwm_out(unsigned int pwmv);

#endif

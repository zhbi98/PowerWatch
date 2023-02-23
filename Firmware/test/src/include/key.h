
#ifndef __KEY_H__
#define __KEY_H__

#include <stdbool.h>
#include "gd32f10x.h"

#define KEY1_GPIO  GPIOC
#define KEY1_PIN   GPIO_PIN_14
#define KEY1_CLOCK RCU_GPIOC

#define KEY2_GPIO  GPIOC
#define KEY2_PIN   GPIO_PIN_13
#define KEY2_CLOCK RCU_GPIOC

#define KEY3_GPIO  GPIOB
#define KEY3_PIN   GPIO_PIN_7
#define KEY3_CLOCK RCU_GPIOB

#define KEY4_GPIO  GPIOB
#define KEY4_PIN   GPIO_PIN_6
#define KEY4_CLOCK RCU_GPIOB

#define KEY1_EVT   ('1')
#define KEY2_EVT   ('2')
#define KEY3_EVT   ('3')
#define KEY4_EVT   ('4')
#define RELEASE    ('0')

#define KEY1_STATUS() gpio_input_bit_get(KEY1_GPIO, KEY1_PIN)
#define KEY2_STATUS() gpio_input_bit_get(KEY2_GPIO, KEY2_PIN)
#define KEY3_STATUS() gpio_input_bit_get(KEY3_GPIO, KEY3_PIN)
#define KEY4_STATUS() gpio_input_bit_get(KEY4_GPIO, KEY4_PIN)

struct key_event_t {
    // false: short pressed event
    // true : long pressed event
    bool press_long;
    // duration pressed time
    unsigned int press_duration;
    // pressed active speed
    unsigned int active_time;
};

extern struct key_event_t key_evt;

extern void key_gpio_init();
extern unsigned char key_drive_code();
extern void key_event_ticks();
extern unsigned char read_key_event();

#endif

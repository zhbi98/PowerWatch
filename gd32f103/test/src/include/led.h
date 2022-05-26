
#ifndef __LED_H__
#define __LED_H__

#include "gd32f10x.h"

#define LED1_GPIO  GPIOA
#define LED1_PIN   GPIO_PIN_1
#define LED1_CLOCK RCU_GPIOA

#define LED2_GPIO  GPIOA
#define LED2_PIN   GPIO_PIN_2
#define LED2_CLOCK RCU_GPIOA

enum led_status {
    LED_OFF = 0,
    LED_ON  = 1,
};

// Period is running tick
enum led_period {
    ON_PERIOD  = 5,
    OFF_PERIOD = 10,
};

struct led_obj_t {
    unsigned int turn_on_period;
    unsigned int turn_off_period;
    unsigned char last_status;
    unsigned char status;
    void (* led_cb)(unsigned char status);
};

extern struct led_obj_t led2;
extern void led_controller_handler(struct led_obj_t * led);
extern void led2_controller_cb(unsigned char status);

extern void led1_gpio_init();
extern void led2_gpio_init();
extern void led1_set_status(unsigned char status);
extern void led2_set_status(unsigned char status);

#endif


#ifndef __LED_H__
#define __LED_H__

#include "gd32f30x.h"
#include "time.h"

#define SYSTEM_GREEN_LIGHT 0
#define SYSTEM_RED_LIGHT   1

#define STATUS_LED_GPIO    GPIOE
#define STATUS_LED_PIN     GPIO_PIN_3
#define STATUS_LED_CLOCK   RCU_GPIOE

#define DEBUG_LED_GPIO     GPIOC
#define DEBUG_LED_PIN      GPIO_PIN_14
#define DEBUG_LED_CLOCK    RCU_GPIOC

struct led_display_t {
    unsigned int HIGH_TIME;
    unsigned int LOW_TIME;

    unsigned int dsp_time;
    unsigned char status;
};

extern struct led_display_t sled_display;
extern struct led_display_t dled_display;

extern void status_led_event_timing();
extern void status_led_gpio_init();
extern void status_led_onff(unsigned char status);
extern void status_led_twink();

extern void debug_led_event_timing();
extern void debug_led_gpio_init();
extern void debug_led_onff(unsigned char status);
extern void debug_led_display(unsigned int t);
extern void debug_led_twink();
static void debug_led_breath_period(unsigned int period, unsigned int time_l);
extern void debug_led_breath();

#endif

/**
 * @file led.h
 *
 */

#ifndef __LED_H__
#define __LED_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>
#include "gd32f10x.h"

/*********************
 *      DEFINES
 *********************/

#define MS_TO_TICKS(ms, base) \
    ((uint32_t)((ms) / (base)))

/**********************
 *      TYPEDEFS
 **********************/

enum {
    LED_OFF = 0,
    LED_ON,
};
typedef uint8_t led_state_t;

typedef struct {
    uint32_t on_tick;
    uint32_t off_tick;
    uint8_t state;
    uint8_t last_state;
    void (* led_cb)(uint8_t state);
} led_obj_t;

extern led_obj_t led1;
extern led_obj_t led2;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void led_gpio_init();
void led_light_work(led_obj_t * led);

#endif

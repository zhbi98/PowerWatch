/**
 * @file backlight.h
 *
 */

#ifndef __BL_H__
#define __BL_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include "st7789.h"

/*********************
 *      DEFINES
 *********************/

#define SECOND_TO_TICKS(s, base) \
    ((uint32_t)((s) * (1000U) / (base)))

/**********************
 *      TYPEDEFS
 **********************/

enum {
    LCD_STATE_OFF = 0,
    LCD_STATE_ON,
};

typedef uint8_t lcd_light_state_t;

typedef struct {
    uint32_t tick;
    uint8_t state;
} lcd_light_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lcd_light_set_state(uint8_t state);
void lcd_light_reset_state();
void lcd_light_repeat_state();
void lcd_light_work();
uint8_t lcd_light_get_state();

#endif /*__BL_H__*/

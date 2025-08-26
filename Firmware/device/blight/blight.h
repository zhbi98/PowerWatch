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

#define TICKS(v1, v2) \
    (((uint32_t)(v1)) / ((uint32_t)(v2)))

#define STS_TICKS(s1, s2) \
    ((uint32_t)((s1) / (s2)))

#define STMS_TICKS(s, ms) \
    ((uint32_t)((s) * (1000U) / (ms)))

#define MSTMS_TICKS(ms1, ms2) \
    ((uint32_t)((ms1) / (ms2)))

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

void lcd_light_state_reset();
void lcd_light_state_repeat();
void lcd_light_state_work();
void lcd_light_set_state(bool state);
bool lcd_light_get_state();

#endif /*__BL_H__*/

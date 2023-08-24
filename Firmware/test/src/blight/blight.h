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

#define ONTIME 3000U

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    uint32_t ontime;
    uint8_t state;
} lcd_blight_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void blight_set_state(uint8_t state);
uint8_t blight_get_state();
void blight_beat_state();
void blight_tick();

#endif /*__BL_H__*/

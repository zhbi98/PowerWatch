/**
 * @file backlight.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "blight.h"

/**********************
 *      TYPEDEFS
 **********************/

lcd_blight_t blight = {
    .ontime = ONTIME,
    .state = 1,
};

/**********************
 * GLOBAL FUNCTIONS
 **********************/

void blight_set_state(uint8_t state)
{
    blight.state = state;
    if (!state) blight.ontime = 0;
    else blight.ontime = ONTIME;
}

uint8_t blight_get_state()
{
    return blight.state;
}

void blight_beat_state()
{
    if (blight_get_state()) blight_set_state(0);
    else blight_set_state(1);
}

void blight_tick()
{
    if (blight.ontime != 0)
        blight.ontime--;
    if (!blight.ontime) {
        ST7789_BL_H();
        blight.state = 0;
    } else ST7789_BL_L();
}

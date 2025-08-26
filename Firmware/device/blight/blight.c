/**
 * @file backlight.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "blight.h"

/*********************
 *      DEFINES
 *********************/

#define LCD_ONTIME  60U /*s*/
#define LCD_REPEAT 100U /*ms*/

/**********************
 *      TYPEDEFS
 **********************/

lcd_light_t lcd_light = {
    .state = LCD_STATE_ON,
    .tick = STMS_TICKS(
        LCD_ONTIME, 
        LCD_REPEAT
    ),
};

/**********************
 * GLOBAL FUNCTIONS
 **********************/

/**
 * Reset status and time of light.
 */
void lcd_light_state_reset()
{
    if (lcd_light.state) return;
    if (lcd_light.tick) return;

    lcd_light.state = true;
    lcd_light.tick = STMS_TICKS(
        LCD_ONTIME, 
        LCD_REPEAT
    );
    ST7789_BL_L();
}

/**
 * Repeated execution will perform the opposite operation once.
 */
void lcd_light_state_repeat()
{
    if (!lcd_light.state) {
        lcd_light.state = true;
        ST7789_BL_L();
        lcd_light.tick = STMS_TICKS(
            LCD_ONTIME, 
            LCD_REPEAT
        );
    } else {
        lcd_light.state = false;
        ST7789_BL_H();
        lcd_light.tick = STMS_TICKS(0, 
            LCD_REPEAT
        );
    }
}

/**
 * Automatic logical calls to perform close-related 
 * operations after a period of time.
 */
void lcd_light_state_work()
{
    if (!lcd_light.state) return;
    if (lcd_light.tick > 0) 
        lcd_light.tick--;

    if (!lcd_light.tick) {
        lcd_light.state = false;
        ST7789_BL_H();
        lcd_light.tick = STMS_TICKS(0, 
            LCD_REPEAT
        );
    }
}

/**
 * Sets the state of the statbar light state.
 * @param state light state.
 */
void lcd_light_set_state(bool state)
{
    if (state != lcd_light.state) {
        lcd_light.state = state;

        if (state) {
            ST7789_BL_L();
            lcd_light.tick = STMS_TICKS(
                LCD_ONTIME, 
                LCD_REPEAT
            );
        } else {
            ST7789_BL_H();
            lcd_light.tick = STMS_TICKS(0, 
                LCD_REPEAT
            );
        }
    }
}

/**
 * gets the state of the statbar light state.
 * @return light state.
 */
bool lcd_light_get_state()
{
    return lcd_light.state;
}

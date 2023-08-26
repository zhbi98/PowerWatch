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
    .tick = SECOND_TO_TICKS(
        LCD_ONTIME, 
        LCD_REPEAT
    ),
};

/**********************
 * GLOBAL FUNCTIONS
 **********************/

void lcd_light_set_state(uint8_t state)
{
    lcd_light.tick = (state) ? 
        SECOND_TO_TICKS(
            LCD_ONTIME, 
            LCD_REPEAT
        ) : 0;

    lcd_light.state = state;
    (state) ? ST7789_BL_L() : ST7789_BL_H();
}

void lcd_light_reset_state()
{
    lcd_light.tick = SECOND_TO_TICKS(
        LCD_ONTIME, LCD_REPEAT);

    lcd_light.state = LCD_STATE_ON;
    ST7789_BL_L();
}

void lcd_light_repeat_state()
{
    uint8_t state = lcd_light_get_state();
    (state) ? lcd_light_set_state(LCD_STATE_OFF) : 
    lcd_light_set_state(LCD_STATE_ON);
}

void lcd_light_watch()
{
    if (lcd_light.tick > 0)
        lcd_light.tick--;

    if ((!lcd_light.tick) && (lcd_light.state)) {
        lcd_light.state = LCD_STATE_OFF;
        ST7789_BL_H();
    }
}

uint8_t lcd_light_get_state()
{
    return lcd_light.state;
}

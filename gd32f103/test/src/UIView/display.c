
#include "display.h"

struct display_controller_t display_controller = {
    .time = TIME_5MIN,
    .status = true,
};

void display_off_hanlder()
{
    if (display_controller.time <= 0) {
        display_controller.status = false;
        ST7789_BL_H();
    } else
        display_controller.time--;
}

void display_event_handler()
{
    if (display_controller.status == true) {
        display_controller.status = false;
        display_controller.time = 0;
        ST7789_BL_H();
    } else {
        display_controller.status = true;
        display_controller.time = TIME_5MIN;
        ST7789_BL_L();
    }
    sleep_ms(1000);
}

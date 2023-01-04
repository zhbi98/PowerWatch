
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdbool.h>
#include "st7789.h"

#define TIME_5MIN (300 / 0.1)

struct display_controller_t {
    unsigned int time;
    unsigned char status;
};

extern void display_off_hanlder();
extern void display_event_handler();

#endif

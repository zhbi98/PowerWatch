
#include "key.h"

struct key_event_t key_evt = {
    .press_long = false,
    .press_duration = 8000,
    .active_time = 800,
};

void key_gpio_init()
{
    rcu_periph_clock_enable(KEY1_CLOCK);
    rcu_periph_clock_enable(KEY2_CLOCK);
    rcu_periph_clock_enable(KEY3_CLOCK);
    rcu_periph_clock_enable(KEY4_CLOCK);

    gpio_init(KEY1_GPIO, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, KEY1_PIN);
    gpio_init(KEY2_GPIO, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, KEY2_PIN);
    gpio_init(KEY3_GPIO, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, KEY3_PIN);
    gpio_init(KEY4_GPIO, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, KEY4_PIN);
}

unsigned char key_drive_code()
{
    unsigned char t = 0x00;

    /**
     * [1110, 1111], <k1, k2, k3, k4, 1, 1, 1, 1>
     * Key follow the code:
     * Key <1> <0x7f>
     * Key <2> <0xbf>
     * Key <3> <0xdf>
     * Key <4> <0xef>
     */
    t = (t << 1) | KEY1_STATUS();
    t = (t << 1) | KEY2_STATUS();
    t = (t << 1) | KEY3_STATUS();
    t = (t << 1) | KEY4_STATUS();
    t = (t << 1) | (0x01);
    t = (t << 1) | (0x01);
    t = (t << 1) | (0x01);
    t = (t << 1) | (0x01);

    return t;
}

void key_event_ticks()
{
    if (key_evt.press_duration > 0) {
        key_evt.press_duration--;
    }
    if (key_evt.active_time > 0) {
        key_evt.active_time--;
    }
}

unsigned char read_key_event()
{
    static unsigned char last_event = RELEASE;
    unsigned char k = 0;
    unsigned char drive_code = key_drive_code();

    switch (drive_code) {
        case 0x7f:
            k = KEY1_EVT;
            break;
        case 0xbf:
            k = KEY2_EVT;
            break;
        case 0xdf:
            k = KEY3_EVT;
            break;
        case 0xef:
            k = KEY4_EVT;
            break;
        default:
            k = RELEASE;
            break;
    }

    if (k == RELEASE) {
        key_evt.press_duration = 8000;
    }

    // key 5 unsupport long press auto trigger active  
    if ((key_evt.press_duration <= 0)/* && (k != KEY5_EVT)*/) {
        key_evt.press_long = true;
    } else {
        key_evt.press_long = false;
    }

    key_event_ticks();

    if (key_evt.press_long == true) {
        if (key_evt.active_time <= 0) {
            key_evt.active_time = 800;
            return k;
        } else {
            return RELEASE;
        }
    }

    // LVGL KEY FORMAT
    // return k;

    // Pressed event
    // if ((k != RELEASE) && (last_event == RELEASE)) {
    //     last_event = k;
    //     return k;
    // } else {
    //     last_event = k;
    //     return RELEASE;
    // }

    // Released event
    if ((k == RELEASE) && (last_event != RELEASE)) {
        drive_code = last_event;
        last_event = RELEASE;
        return drive_code;
    } else {
        last_event = k;
        return RELEASE;
    }
}

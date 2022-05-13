
#include "led.h"

struct led_display_t sled_display = {
    .HIGH_TIME = 30000,
    .LOW_TIME = 30000,
    .dsp_time = 0,
    .status = 0,
};

void status_led_event_timing()
{
    if (sled_display.dsp_time != 0) {
        sled_display.dsp_time--;
    }
}

void status_led_gpio_init()
{
    rcu_periph_clock_enable(STATUS_LED_CLOCK);
    gpio_init(STATUS_LED_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, STATUS_LED_PIN);
}

void status_led_onff(unsigned char status)
{
    if (!status) {
        gpio_bit_reset(STATUS_LED_GPIO, STATUS_LED_PIN);
    } else {
        gpio_bit_set(STATUS_LED_GPIO, STATUS_LED_PIN);
    }
}

void status_led_twink()
{
    if (!sled_display.status) {
        if (sled_display.dsp_time) {
            gpio_bit_reset(STATUS_LED_GPIO, STATUS_LED_PIN);
        } else {
            sled_display.status = !sled_display.status;
            sled_display.dsp_time = sled_display.HIGH_TIME;
        }
    } else {
        if (sled_display.dsp_time) {
            gpio_bit_set(STATUS_LED_GPIO, STATUS_LED_PIN);
        } else {
            sled_display.status = !sled_display.status;
            sled_display.dsp_time = sled_display.LOW_TIME;
        }
    }

    status_led_event_timing();
}

struct led_display_t dled_display = {
    .HIGH_TIME = 100,
    .LOW_TIME = 1600,
    .dsp_time = 0,
    .status = 0,
};

void debug_led_event_timing()
{
    if (dled_display.dsp_time != 0) {
        dled_display.dsp_time--;
    }
}

void debug_led_gpio_init()
{
    rcu_periph_clock_enable(DEBUG_LED_CLOCK);
    gpio_init(DEBUG_LED_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, DEBUG_LED_PIN);
}

void debug_led_onff(unsigned char status)
{
    if (!status) {
        gpio_bit_reset(DEBUG_LED_GPIO, DEBUG_LED_PIN);
    } else {
        gpio_bit_set(DEBUG_LED_GPIO, DEBUG_LED_PIN);
    }
}

void debug_led_display(unsigned int t)
{
    for (; t > 0; t--) {
        gpio_bit_reset(DEBUG_LED_GPIO, DEBUG_LED_PIN);
        sleep_ms(20);
        gpio_bit_set(DEBUG_LED_GPIO, DEBUG_LED_PIN);
        sleep_ms(20);
    }
}

void debug_led_twink()
{
    if (!dled_display.status) {
        if (dled_display.dsp_time) {
            gpio_bit_reset(DEBUG_LED_GPIO, DEBUG_LED_PIN);
        } else {
            dled_display.status = !dled_display.status;
            dled_display.dsp_time = dled_display.HIGH_TIME;
        }
    } else {
        if (dled_display.dsp_time) {
            gpio_bit_set(DEBUG_LED_GPIO, DEBUG_LED_PIN);
        } else {
            dled_display.status = !dled_display.status;
            dled_display.dsp_time = dled_display.LOW_TIME;
        }
    }

    debug_led_event_timing();
}

static void debug_led_breath_period(unsigned int period, unsigned int time_l)
{
    unsigned int time_h;

    time_h = period - time_l;

    gpio_bit_reset(DEBUG_LED_GPIO, DEBUG_LED_PIN);
    while (time_l--);
    gpio_bit_set(DEBUG_LED_GPIO, DEBUG_LED_PIN);
    while (time_h--);
}

void debug_led_breath()
{
    unsigned int i;

    for (i = 0; i < 8000; i++) {
        debug_led_breath_period(8000, i);
    }
    for (i = 8000; i > 0; i--) {
        debug_led_breath_period(8000, i);
    }  
}


#include "led.h"

/*********************************
 *    LED CONTROLLER IMPLEMENT
 *********************************/

led_obj_t led2 = {
    .turn_on_period = ON_PERIOD,
    .turn_off_period = OFF_PERIOD,
    .last_status = LED_OFF,
    .status = LED_OFF,
    .led_cb = led2_controller_cb,
};

void led_controller_handler(led_obj_t * led)
{
    if (led->status == LED_ON) {
        led->turn_on_period--;
        if (led->turn_on_period <= 0) {
            led->status = LED_OFF;
            led->turn_off_period = OFF_PERIOD;
        }
    } else {
        led->turn_off_period--;
        if (led->turn_off_period <= 0) {
            led->status = LED_ON;
            led->turn_on_period = ON_PERIOD;
        }
    }

    if (led->status != led->last_status) {
        led->led_cb(led->status);
    }

    led->last_status = led->status;
}

void led2_controller_cb(uint8_t status)
{
    /*led1_set_status(!status);*/
    led2_set_status(!status);
}

/*********************************
 *    LED HARDWARE IMPLEMENT
 *********************************/

void led1_gpio_init()
{
    rcu_periph_clock_enable(LED1_CLOCK);
    gpio_init(LED1_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED1_PIN);
}

void led2_gpio_init()
{
    rcu_periph_clock_enable(LED2_CLOCK);
    gpio_init(LED2_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED2_PIN);
}

void led1_set_status(uint8_t status)
{
    if (status) gpio_bit_set(LED1_GPIO, LED1_PIN);
    else gpio_bit_reset(LED1_GPIO, LED1_PIN);
}

void led2_set_status(uint8_t status)
{
    if (status) gpio_bit_set(LED2_GPIO, LED2_PIN);
    else gpio_bit_reset(LED2_GPIO, LED2_PIN);
}

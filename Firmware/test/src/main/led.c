/**
 * @file led.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "led.h"

/*********************
 *      DEFINES
 *********************/

#define LED_ONTIME  200U /*ms*/
#define LED_OFFTIME 1000U /*ms*/
#define LED_REPEAT  100U /*ms*/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void led1_set_state(uint8_t state);
static void led2_set_state(uint8_t state);

/**********************
 *      TYPEDEFS
 **********************/

led_obj_t led1 = {
    .on_tick = MS_TO_TICKS(
        LED_ONTIME, LED_REPEAT),
    .off_tick = MS_TO_TICKS(
        LED_OFFTIME, LED_REPEAT),

    .last_state = LED_OFF,
    .state = LED_OFF,
    .led_cb = led1_set_state,
};

led_obj_t led2 = {
    .on_tick = MS_TO_TICKS(
        LED_ONTIME, LED_REPEAT),
    .off_tick = MS_TO_TICKS(
        LED_OFFTIME, LED_REPEAT),

    .last_state = LED_OFF,
    .state = LED_OFF,
    .led_cb = led2_set_state,
};

/**********************
 * GLOBAL FUNCTIONS
 **********************/

void led_gpio_init()
{
    /*LED 1*/
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(
        GPIOA, GPIO_MODE_OUT_PP, 
        GPIO_OSPEED_50MHZ, GPIO_PIN_1
    );
    /*LED2*/
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(
        GPIOA, GPIO_MODE_OUT_PP, 
        GPIO_OSPEED_50MHZ, GPIO_PIN_2
    );
}

void led1_set_state(uint8_t state)
{
    if (!state) gpio_bit_set(GPIOA, GPIO_PIN_1);
    else gpio_bit_reset(GPIOA, GPIO_PIN_1);
}

void led2_set_state(uint8_t state)
{
    if (!state) gpio_bit_set(GPIOA, GPIO_PIN_2);
    else gpio_bit_reset(GPIOA, GPIO_PIN_2);
}

void led_light_work(led_obj_t * led)
{
    if (led->state == LED_ON) {
        led->on_tick--;
        if (led->on_tick <= 0) {
            led->state = LED_OFF;
            led->off_tick = MS_TO_TICKS(
                LED_OFFTIME, LED_REPEAT);
        }
    } else {
        led->off_tick--;
        if (led->off_tick <= 0) {
            led->state = LED_ON;
            led->on_tick = MS_TO_TICKS(
                LED_ONTIME, LED_REPEAT);
        }
    }

    if (led->state != led->last_state) {
        led->led_cb(led->state);
    }

    led->last_state = led->state;
}

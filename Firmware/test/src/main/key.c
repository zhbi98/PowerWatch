/**
 * @file key.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "key.h"

/*********************
 *      DEFINES
 *********************/

#define KEY_DURATION 3U /*s*/
#define KEY_ACT_TIME 1U /*s*/
#define KEY_REPEAT 100U /*ms*/

/**********************
 *      TYPEDEFS
 **********************/

key_evt_t key_evt = {
    .duration = SECOND_TO_TICKS(KEY_DURATION, KEY_REPEAT), 
    .act_time = SECOND_TO_TICKS(KEY_ACT_TIME, KEY_REPEAT),
    .lpress = false,
};

/**********************
 * STATIC PROTOTYPES
 **********************/

static uint8_t key_drive_code();
static void key_event_ticks();

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void key_gpio_init()
{
    rcu_periph_clock_enable(
        RCU_GPIOC);
    rcu_periph_clock_enable(
        RCU_GPIOC);
    rcu_periph_clock_enable(
        RCU_GPIOB);
    rcu_periph_clock_enable(
        RCU_GPIOB);

    gpio_init(
        GPIOC, GPIO_MODE_IPU, 
        GPIO_OSPEED_50MHZ, 
        GPIO_PIN_14
    );

    gpio_init(
        GPIOC, GPIO_MODE_IPU, 
        GPIO_OSPEED_50MHZ, 
        GPIO_PIN_13
    );

    gpio_init(
        GPIOB, GPIO_MODE_IPU, 
        GPIO_OSPEED_50MHZ, 
        GPIO_PIN_7
    );

    gpio_init(
        GPIOB, GPIO_MODE_IPU, 
        GPIO_OSPEED_50MHZ, 
        GPIO_PIN_6
    );
}

static uint8_t key_drive_code()
{
    uint8_t dcode = 0x0F;
    uint8_t res[4] = {0};

    res[0] = KEY1_STATUS();
    res[1] = KEY2_STATUS();
    res[2] = KEY3_STATUS();
    res[3] = KEY4_STATUS();

    for (uint8_t i = 0; i < 4; i++) {
        res[i] = res[i] & 0x01;
        res[i] <<= (7 - i);
        dcode |= res[i];
    }
    return dcode;
}

static void key_event_ticks()
{
    if (key_evt.duration > 0) 
        key_evt.duration--;
    if (key_evt.act_time > 0) 
        key_evt.act_time--;
}

uint8_t key_read_event()
{
    static uint8_t last_event = RELEASE;
    uint8_t drive_code = key_drive_code();
    uint8_t event = RELEASE;

    switch (drive_code) {
    case 0x7F:
        event = KEY1_EVT;
        break;
    case 0xBF:
        event = KEY2_EVT;
        break;
    case 0xDF:
        event = KEY3_EVT;
        break;
    case 0xEF:
        event = KEY4_EVT;
        break;
    default:
        event = RELEASE;
        break;
    }

#if 0
    if (event == RELEASE) key_evt.duration = SECOND_TO_TICKS(
        KEY_DURATION, KEY_REPEAT);
    if (key_evt.duration <= 0) key_evt.lpress = true;
    else key_evt.lpress = false;
#endif

    key_event_ticks();

#if 0
    /*Press and hold the key event*/
    if (key_evt.lpress) {
        if (key_evt.act_time <= 0) {
            key_evt.act_time = SECOND_TO_TICKS(
                KEY_ACT_TIME, KEY_REPEAT);
            return event;
        } else {
            return RELEASE;
        }
    }
#endif

#if 0
    /*Key press events*/
    if (
        (event != RELEASE) && 
        (last_event == RELEASE)
    ) {
        last_event = event;
        return event;
    } else {
        last_event = event;
        return RELEASE;
    }
#endif

    /*Key lift event*/
    if (
        (event == RELEASE) && 
        (last_event != RELEASE)
    ) {
        drive_code = last_event;
        last_event = RELEASE;
        return drive_code;
    } else {
        last_event = event;
        return RELEASE;
    }
}

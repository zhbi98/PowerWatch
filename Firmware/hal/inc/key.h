/**
 * @file key.h
 *
 */

#ifndef __KEY_H__
#define __KEY_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include <stdint.h>
#include "gd32f10x.h"

/*********************
 *      DEFINES
 *********************/

#define SECOND_TO_TICKS(s, base) \
    ((uint32_t)((s) * (1000U) / (base)))

#define KEY1_STATUS() \
    gpio_input_bit_get(GPIOC, GPIO_PIN_14)
#define KEY2_STATUS() \
    gpio_input_bit_get(GPIOC, GPIO_PIN_13)
#define KEY3_STATUS() \
    gpio_input_bit_get(GPIOB, GPIO_PIN_7)
#define KEY4_STATUS() \
    gpio_input_bit_get(GPIOB, GPIO_PIN_6)

/**********************
 *      TYPEDEFS
 **********************/

enum {
    KEY1_EVT = '0',
    KEY2_EVT,
    KEY3_EVT,
    KEY4_EVT,
    RELEASE,
};

typedef uint8_t key_evt_code_t;

typedef struct {
    bool lpress;      /**< duration pressed time*/
    uint32_t duration; /**< duration pressed time*/
    uint32_t act_time; /**< pressed active speed*/
} key_evt_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void key_gpio_init();
uint8_t key_read_event();

#endif /*__KEY_H__*/

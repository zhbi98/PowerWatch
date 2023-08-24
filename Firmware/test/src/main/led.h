
#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>
#include "gd32f10x.h"

#define LED1_GPIO  GPIOA
#define LED1_PIN   GPIO_PIN_1
#define LED1_CLOCK RCU_GPIOA

#define LED2_GPIO  GPIOA
#define LED2_PIN   GPIO_PIN_2
#define LED2_CLOCK RCU_GPIOA

enum {
    LED_OFF = 0,
    LED_ON,
};
typedef uint8_t led_state_t;

/*Period is running tick*/
enum {
    ON_PERIOD  = 1,
    OFF_PERIOD = 2,
};

typedef struct {
    uint32_t turn_on_period;
    uint32_t turn_off_period;
    uint8_t last_status;
    uint8_t status;
    void (* led_cb)(uint8_t status);
} led_obj_t;

extern led_obj_t led2;
extern void led_controller_handler(led_obj_t * led);
extern void led2_controller_cb(uint8_t status);

extern void led1_gpio_init();
extern void led2_gpio_init();
extern void led1_set_status(uint8_t status);
extern void led2_set_status(uint8_t status);

#endif

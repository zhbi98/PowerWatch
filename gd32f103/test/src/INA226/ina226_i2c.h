
#ifndef __INA226_I2C_H__
#define __INA226_I2C_H__

#include "gd32f10x.h"
#include "time.h"

#define INA226_SDA_GPIO   GPIOB
#define INA226_SDA_PIN    GPIO_PIN_15
#define INA226_SDA_CLOCK  RCU_GPIOB

#define INA226_SCL_GPIO   GPIOB
#define INA226_SCL_PIN    GPIO_PIN_13
#define INA226_SCL_CLOCK  RCU_GPIOB

#define INA226_SDA_H()    gpio_bit_set(INA226_SDA_GPIO, INA226_SDA_PIN)
#define INA226_SDA_L()    gpio_bit_reset(INA226_SDA_GPIO, INA226_SDA_PIN)

#define INA226_SCL_H()    gpio_bit_set(INA226_SCL_GPIO, INA226_SCL_PIN)
#define INA226_SCL_L()    gpio_bit_reset(INA226_SCL_GPIO, INA226_SCL_PIN)

#define READ_INA226_SDA() gpio_input_bit_get(INA226_SDA_GPIO, INA226_SDA_PIN)

static void ina226_sleep_us(unsigned int us);

extern void ina226_gpio_init();
extern void ina226_sda_out_mode();
extern void ina226_sda_in_mode();
extern void ina226_i2c_start();
extern void ina226_i2c_stop();
extern unsigned char ina226_i2c_wait_ack();
extern void ina226_i2c_ack();
extern void ina226_i2c_nack();
extern void ina226_i2c_send_byte(unsigned char a_byte);
extern unsigned char ina226_i2c_read_byte(unsigned char ack);

#endif

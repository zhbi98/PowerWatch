
#ifndef __ST7789_H__
#define __ST7789_H__

#include "gd32f10x.h"
#include "time.h"

#define ST7789_RST_GPIO  GPIOA
#define ST7789_RST_PIN   GPIO_PIN_6
#define ST7789_RST_CLOCK RCU_GPIOA

#define ST7789_CS_GPIO  GPIOA
#define ST7789_CS_PIN   GPIO_PIN_4
#define ST7789_CS_CLOCK RCU_GPIOA

#define ST7789_DC_GPIO  GPIOA
#define ST7789_DC_PIN   GPIO_PIN_5
#define ST7789_DC_CLOCK RCU_GPIOA

#define ST7789_WR_GPIO  GPIOA
#define ST7789_WR_PIN   GPIO_PIN_7
#define ST7789_WR_CLOCK RCU_GPIOA

#define ST7789_RD_GPIO  GPIOA//GPIOA
#define ST7789_RD_PIN   GPIO_PIN_3//GPIO_PIN_8 // 
#define ST7789_RD_CLOCK RCU_GPIOA//RCU_GPIOA

#define ST7789_D0_GPIO  GPIOB
#define ST7789_D0_PIN   GPIO_PIN_0
#define ST7789_D0_CLOCK RCU_GPIOB

#define ST7789_D1_GPIO  GPIOB
#define ST7789_D1_PIN   GPIO_PIN_1
#define ST7789_D1_CLOCK RCU_GPIOB

#define ST7789_D2_GPIO  GPIOB
#define ST7789_D2_PIN   GPIO_PIN_2
#define ST7789_D2_CLOCK RCU_GPIOB

#define ST7789_D3_GPIO  GPIOB
#define ST7789_D3_PIN   GPIO_PIN_3
#define ST7789_D3_CLOCK RCU_GPIOB

#define ST7789_D4_GPIO  GPIOD//GPIOB
#define ST7789_D4_PIN   GPIO_PIN_2//GPIO_PIN_4 // 
#define ST7789_D4_CLOCK RCU_GPIOD//RCU_GPIOB

#define ST7789_D5_GPIO  GPIOB
#define ST7789_D5_PIN   GPIO_PIN_5
#define ST7789_D5_CLOCK RCU_GPIOB

#define ST7789_D6_GPIO  GPIOB
#define ST7789_D6_PIN   GPIO_PIN_6
#define ST7789_D6_CLOCK RCU_GPIOB

#define ST7789_D7_GPIO  GPIOB
#define ST7789_D7_PIN   GPIO_PIN_7
#define ST7789_D7_CLOCK RCU_GPIOB

#define ST7789_RST_H() gpio_bit_set(ST7789_RST_GPIO, ST7789_RST_PIN)
#define ST7789_RST_L() gpio_bit_reset(ST7789_RST_GPIO, ST7789_RST_PIN)

#define ST7789_CS_H() gpio_bit_set(ST7789_CS_GPIO, ST7789_CS_PIN)
#define ST7789_CS_L() gpio_bit_reset(ST7789_CS_GPIO, ST7789_CS_PIN)

#define ST7789_DC_H() gpio_bit_set(ST7789_DC_GPIO, ST7789_DC_PIN)
#define ST7789_DC_L() gpio_bit_reset(ST7789_DC_GPIO, ST7789_DC_PIN)

#define ST7789_WR_H() gpio_bit_set(ST7789_WR_GPIO, ST7789_WR_PIN)
#define ST7789_WR_L() gpio_bit_reset(ST7789_WR_GPIO, ST7789_WR_PIN)

#define ST7789_RD_H() gpio_bit_set(ST7789_RD_GPIO, ST7789_RD_PIN)
#define ST7789_RD_L() gpio_bit_reset(ST7789_RD_GPIO, ST7789_RD_PIN)

#define ST7789_D0_SET(x) gpio_bit_write(ST7789_D0_GPIO, ST7789_D0_PIN, x)
#define ST7789_D1_SET(x) gpio_bit_write(ST7789_D1_GPIO, ST7789_D1_PIN, x)
#define ST7789_D2_SET(x) gpio_bit_write(ST7789_D2_GPIO, ST7789_D2_PIN, x)
#define ST7789_D3_SET(x) gpio_bit_write(ST7789_D3_GPIO, ST7789_D3_PIN, x)
#define ST7789_D4_SET(x) gpio_bit_write(ST7789_D4_GPIO, ST7789_D4_PIN, x)
#define ST7789_D5_SET(x) gpio_bit_write(ST7789_D5_GPIO, ST7789_D5_PIN, x)
#define ST7789_D6_SET(x) gpio_bit_write(ST7789_D6_GPIO, ST7789_D6_PIN, x)
#define ST7789_D7_SET(x) gpio_bit_write(ST7789_D7_GPIO, ST7789_D7_PIN, x)

// ST7789V3
#define TFT_WIDTH  320
#define TFT_HEIGHT 170

extern void st7789_gpio_init();
extern void st7789_bus(unsigned char data);
extern void write_command(unsigned char command);
extern void write_data(unsigned char data);
extern void write_datas(unsigned int data);
extern void st7789_reset();
extern void st7789_direction(unsigned char direction);
extern void st7789_init();
extern void display_position(unsigned int y, unsigned int x);
extern void display_region(unsigned int y, unsigned int x, unsigned int width, unsigned int height);
extern void display_pixel(unsigned int y, unsigned int x, unsigned int color);
extern void tft_clear(unsigned int color);

#endif


#ifndef __ST7789_H__
#define __ST7789_H__

#include "gd32f10x.h"
#include "time.h"

#define ST7789_BL_GPIO   GPIOB
#define ST7789_BL_PIN    GPIO_PIN_12
#define ST7789_BL_CLOCK  RCU_GPIOB

#define ST7789_RST_GPIO  GPIOB
#define ST7789_RST_PIN   GPIO_PIN_5
#define ST7789_RST_CLOCK RCU_GPIOB

#define ST7789_CS_GPIO   GPIOD
#define ST7789_CS_PIN    GPIO_PIN_2
#define ST7789_CS_CLOCK  RCU_GPIOD

#define ST7789_DC_GPIO   GPIOC
#define ST7789_DC_PIN    GPIO_PIN_12
#define ST7789_DC_CLOCK  RCU_GPIOC

#define ST7789_WR_GPIO   GPIOC
#define ST7789_WR_PIN    GPIO_PIN_11
#define ST7789_WR_CLOCK  RCU_GPIOC

#define ST7789_RD_GPIO   GPIOC
#define ST7789_RD_PIN    GPIO_PIN_10
#define ST7789_RD_CLOCK  RCU_GPIOC

#define ST7789_D0_GPIO   GPIOA
#define ST7789_D0_PIN    GPIO_PIN_8
#define ST7789_D0_CLOCK  RCU_GPIOA

#define ST7789_D1_GPIO   GPIOC
#define ST7789_D1_PIN    GPIO_PIN_9
#define ST7789_D1_CLOCK  RCU_GPIOC

#define ST7789_D2_GPIO   GPIOC
#define ST7789_D2_PIN    GPIO_PIN_8
#define ST7789_D2_CLOCK  RCU_GPIOC

#define ST7789_D3_GPIO   GPIOC
#define ST7789_D3_PIN    GPIO_PIN_7
#define ST7789_D3_CLOCK  RCU_GPIOC

#define ST7789_D4_GPIO   GPIOC
#define ST7789_D4_PIN    GPIO_PIN_6
#define ST7789_D4_CLOCK  RCU_GPIOC

#define ST7789_D5_GPIO   GPIOB
#define ST7789_D5_PIN    GPIO_PIN_15
#define ST7789_D5_CLOCK  RCU_GPIOB

#define ST7789_D6_GPIO   GPIOB
#define ST7789_D6_PIN    GPIO_PIN_14
#define ST7789_D6_CLOCK  RCU_GPIOB

#define ST7789_D7_GPIO   GPIOB
#define ST7789_D7_PIN    GPIO_PIN_13
#define ST7789_D7_CLOCK  RCU_GPIOB

#define ST7789_BL_H()  gpio_bit_set(ST7789_BL_GPIO, ST7789_BL_PIN)
#define ST7789_BL_L()  gpio_bit_reset(ST7789_BL_GPIO, ST7789_BL_PIN)

#define ST7789_RST_H() gpio_bit_set(ST7789_RST_GPIO, ST7789_RST_PIN)
#define ST7789_RST_L() gpio_bit_reset(ST7789_RST_GPIO, ST7789_RST_PIN)

#define ST7789_CS_H()  gpio_bit_set(ST7789_CS_GPIO, ST7789_CS_PIN)
#define ST7789_CS_L()  gpio_bit_reset(ST7789_CS_GPIO, ST7789_CS_PIN)

#define ST7789_DC_H()  gpio_bit_set(ST7789_DC_GPIO, ST7789_DC_PIN)
#define ST7789_DC_L()  gpio_bit_reset(ST7789_DC_GPIO, ST7789_DC_PIN)

#define ST7789_WR_H()  gpio_bit_set(ST7789_WR_GPIO, ST7789_WR_PIN)
#define ST7789_WR_L()  gpio_bit_reset(ST7789_WR_GPIO, ST7789_WR_PIN)

#define ST7789_RD_H()  gpio_bit_set(ST7789_RD_GPIO, ST7789_RD_PIN)
#define ST7789_RD_L()  gpio_bit_reset(ST7789_RD_GPIO, ST7789_RD_PIN)

#define ST7789_D0_H()  gpio_bit_set(ST7789_D0_GPIO, ST7789_D0_PIN)
#define ST7789_D0_L()  gpio_bit_reset(ST7789_D0_GPIO, ST7789_D0_PIN)

#define ST7789_D1_H()  gpio_bit_set(ST7789_D1_GPIO, ST7789_D1_PIN)
#define ST7789_D1_L()  gpio_bit_reset(ST7789_D1_GPIO, ST7789_D1_PIN)

#define ST7789_D2_H()  gpio_bit_set(ST7789_D2_GPIO, ST7789_D2_PIN)
#define ST7789_D2_L()  gpio_bit_reset(ST7789_D2_GPIO, ST7789_D2_PIN)

#define ST7789_D3_H()  gpio_bit_set(ST7789_D3_GPIO, ST7789_D3_PIN)
#define ST7789_D3_L()  gpio_bit_reset(ST7789_D3_GPIO, ST7789_D3_PIN)

#define ST7789_D4_H()  gpio_bit_set(ST7789_D4_GPIO, ST7789_D4_PIN)
#define ST7789_D4_L()  gpio_bit_reset(ST7789_D4_GPIO, ST7789_D4_PIN)

#define ST7789_D5_H()  gpio_bit_set(ST7789_D5_GPIO, ST7789_D5_PIN)
#define ST7789_D5_L()  gpio_bit_reset(ST7789_D5_GPIO, ST7789_D5_PIN)

#define ST7789_D6_H()  gpio_bit_set(ST7789_D6_GPIO, ST7789_D6_PIN)
#define ST7789_D6_L()  gpio_bit_reset(ST7789_D6_GPIO, ST7789_D6_PIN)

#define ST7789_D7_H()  gpio_bit_set(ST7789_D7_GPIO, ST7789_D7_PIN)
#define ST7789_D7_L()  gpio_bit_reset(ST7789_D7_GPIO, ST7789_D7_PIN)

/************************
 *    HIGH SPEED GPIO
 ************************/
#define ST7789_CS_HH() (GPIO_BOP(ST7789_CS_GPIO) = (uint32_t)ST7789_CS_PIN)
#define ST7789_CS_LL() (GPIO_BC(ST7789_CS_GPIO) = (uint32_t)ST7789_CS_PIN)

#define ST7789_DC_HH() (GPIO_BOP(ST7789_DC_GPIO) = (uint32_t)ST7789_DC_PIN)
#define ST7789_DC_LL() (GPIO_BC(ST7789_DC_GPIO) = (uint32_t)ST7789_DC_PIN)

#define ST7789_WR_HH() (GPIO_BOP(ST7789_WR_GPIO) = (uint32_t)ST7789_WR_PIN)
#define ST7789_WR_LL() (GPIO_BC(ST7789_WR_GPIO) = (uint32_t)ST7789_WR_PIN)

#define ST7789_RD_HH() (GPIO_BOP(ST7789_RD_GPIO) = (uint32_t)ST7789_RD_PIN)
#define ST7789_RD_LL() (GPIO_BC(ST7789_RD_GPIO) = (uint32_t)ST7789_RD_PIN)

#define ST7789_D0_HH() (GPIO_BOP(ST7789_D0_GPIO) = (uint32_t)ST7789_D0_PIN)
#define ST7789_D0_LL() (GPIO_BC(ST7789_D0_GPIO) = (uint32_t)ST7789_D0_PIN)

#define ST7789_D1_HH() (GPIO_BOP(ST7789_D1_GPIO) = (uint32_t)ST7789_D1_PIN)
#define ST7789_D1_LL() (GPIO_BC(ST7789_D1_GPIO) = (uint32_t)ST7789_D1_PIN)

#define ST7789_D2_HH() (GPIO_BOP(ST7789_D2_GPIO) = (uint32_t)ST7789_D2_PIN)
#define ST7789_D2_LL() (GPIO_BC(ST7789_D2_GPIO) = (uint32_t)ST7789_D2_PIN)

#define ST7789_D3_HH() (GPIO_BOP(ST7789_D3_GPIO) = (uint32_t)ST7789_D3_PIN)
#define ST7789_D3_LL() (GPIO_BC(ST7789_D3_GPIO) = (uint32_t)ST7789_D3_PIN)

#define ST7789_D4_HH() (GPIO_BOP(ST7789_D4_GPIO) = (uint32_t)ST7789_D4_PIN)
#define ST7789_D4_LL() (GPIO_BC(ST7789_D4_GPIO) = (uint32_t)ST7789_D4_PIN)

#define ST7789_D5_HH() (GPIO_BOP(ST7789_D5_GPIO) = (uint32_t)ST7789_D5_PIN)
#define ST7789_D5_LL() (GPIO_BC(ST7789_D5_GPIO) = (uint32_t)ST7789_D5_PIN)

#define ST7789_D6_HH() (GPIO_BOP(ST7789_D6_GPIO) = (uint32_t)ST7789_D6_PIN)
#define ST7789_D6_LL() (GPIO_BC(ST7789_D6_GPIO) = (uint32_t)ST7789_D6_PIN)

#define ST7789_D7_HH() (GPIO_BOP(ST7789_D7_GPIO) = (uint32_t)ST7789_D7_PIN)
#define ST7789_D7_LL() (GPIO_BC(ST7789_D7_GPIO) = (uint32_t)ST7789_D7_PIN)

#define TFT_DIR 1

#if TFT_DIR == 1 || TFT_DIR == 3
#define TFT_WIDTH  (320)
#define TFT_HEIGHT (170)
#endif

#if TFT_DIR == 0 || TFT_DIR == 2
#define TFT_WIDTH  (170)
#define TFT_HEIGHT (320)
#endif

// #define COLOR_ORANGE 0xFD49
// #define COLOR_YELLOW 0xFF95

extern void st7789_gpio_init();
extern void ST7789_DATA_OUT(unsigned char data);
extern void st7789_write_bus(unsigned char data);
extern void write_command(unsigned char command);
extern void write_data(unsigned char data);
extern void write_datas(unsigned short data);
extern void st7789_reset();
extern void st7789_dir(unsigned char dir);
extern void st7789_init();
extern void display_region(unsigned short y, unsigned short x, unsigned short width, unsigned short height);
extern void clear(unsigned short color);

#define ST7789_WRITE_DATA(data)     \
    do {                            \
        ST7789_CS_LL();             \
        ST7789_WR_LL();             \
        ST7789_DATA_OUT(data >> 8); \
        ST7789_WR_HH();             \
        ST7789_CS_HH();             \
                                    \
        ST7789_CS_LL();             \
        ST7789_WR_LL();             \
        ST7789_DATA_OUT(data);      \
        ST7789_WR_HH();             \
        ST7789_CS_HH();             \
    } while (0)

#endif

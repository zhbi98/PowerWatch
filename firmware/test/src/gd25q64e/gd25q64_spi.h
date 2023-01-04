
#ifndef __GD25Q64_SPI_H__
#define __GD25Q64_SPI_H__

#include "gd32f10x.h"
#include "time.h"

#define GD25Q64_CS_GPIO     GPIOA
#define GD25Q64_CS_PIN      GPIO_PIN_5
#define GD25Q64_CS_CLOCK    RCU_GPIOA

#define GD25Q64_SCLK_GPIO   GPIOC
#define GD25Q64_SCLK_PIN    GPIO_PIN_5
#define GD25Q64_SCLK_CLOCK  RCU_GPIOC

#define GD25Q64_MOSI_GPIO   GPIOB
#define GD25Q64_MOSI_PIN    GPIO_PIN_0
#define GD25Q64_MOSI_CLOCK  RCU_GPIOB

#define GD25Q64_MISO_GPIO   GPIOA
#define GD25Q64_MISO_PIN    GPIO_PIN_6
#define GD25Q64_MISO_CLOCK  RCU_GPIOA

#define GD25Q64_CS_H()      gpio_bit_set(GD25Q64_CS_GPIO, GD25Q64_CS_PIN)
#define GD25Q64_CS_L()      gpio_bit_reset(GD25Q64_CS_GPIO, GD25Q64_CS_PIN)

#define GD25Q64_SCLK_H()    gpio_bit_set(GD25Q64_SCLK_GPIO, GD25Q64_SCLK_PIN)
#define GD25Q64_SCLK_L()    gpio_bit_reset(GD25Q64_SCLK_GPIO, GD25Q64_SCLK_PIN)

#define GD25Q64_MOSI_H()    gpio_bit_set(GD25Q64_MOSI_GPIO, GD25Q64_MOSI_PIN)
#define GD25Q64_MOSI_L()    gpio_bit_reset(GD25Q64_MOSI_GPIO, GD25Q64_MOSI_PIN)

#define GD25Q64_MISO_H()    gpio_bit_set(GD25Q64_MISO_GPIO, GD25Q64_MISO_PIN)
#define GD25Q64_MISO_L()    gpio_bit_reset(GD25Q64_MISO_GPIO, GD25Q64_MISO_PIN)

#define READ_GD25Q64_MISO() gpio_input_bit_get(GD25Q64_MISO_GPIO, GD25Q64_MISO_PIN)

static void gd25q64_sleep_us(unsigned int us);

extern void gd25q64_spi_gpio_init();
extern void gd25q64_spi_send_byte(unsigned char byte);
extern unsigned char gd25q64_spi_read_byte();
extern unsigned char gd25q64_spi_write_read_byte(unsigned char data);

#endif

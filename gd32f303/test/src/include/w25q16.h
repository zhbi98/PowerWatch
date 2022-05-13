
#ifndef __W25Q16_H__
#define __W25Q16_H__

#include "gd32f30x.h"
#include "time.h"

#define CURRENT_SPI       SPI1
#define SPI_CLOCK         RCU_SPI1

#define W25Q16_MISO_GPIO  GPIOB
#define W25Q16_MISO_PIN   GPIO_PIN_14
#define W25Q16_MISO_CLOCK RCU_GPIOB

#define W25Q16_MOSI_GPIO  GPIOB
#define W25Q16_MOSI_PIN   GPIO_PIN_15
#define W25Q16_MOSI_CLOCK RCU_GPIOB

#define W25Q16_SCLK_GPIO  GPIOB
#define W25Q16_SCLK_PIN   GPIO_PIN_13
#define W25Q16_SCLK_CLOCK RCU_GPIOB

#define W25Q16_CS_GPIO    GPIOB
#define W25Q16_CS_PIN     GPIO_PIN_12
#define W25Q16_CS_CLOCK   RCU_GPIOB

#define W25Q16_CS_H()     gpio_bit_set(W25Q16_CS_GPIO, W25Q16_CS_PIN)
#define W25Q16_CS_L()     gpio_bit_reset(W25Q16_CS_GPIO, W25Q16_CS_PIN)

#define WRITE_ENABLE      0x06
#define WRITE_DISABLE     0x04
#define READ_STATUS       0x05
#define WRITE_STATUS      0x01
#define READ_DATA         0x03
#define FAST_READ_DATA    0x0b
#define FAST_READ_DUAL    0x3b
#define PAGE_PROGRAM      0x02
#define BLOCK_ERASE       0xd8
#define SECTOR_ERASE      0x20
#define CHIP_ERASE        0xc7
#define POWER_OFF         0xb9
#define RELEASE_POWEROFF  0xab
#define DEVICE_ID         0xab
#define FACT_DEVICE_ID    0x90
#define JEDEC_DEVICE_ID   0x9f

#define W25Q16_ID   	  0xef4014
#define DUMMY_BYTE 		  0xff

extern unsigned char w25q16_data[];

static void w25q16_gpio_init();

extern void w25q16_spibus_init();

static unsigned char w25q16_send_byte(unsigned char a_byte);

extern unsigned char w25q16_receive_byte();
extern uint32_t read_w25q16_id();

static void w25q16_write_enable();
static void tesing_w25q16_busy();

extern void w25q16_power_on();
extern void w25q16_power_off();
extern void w25q16_sector_erase(uint32_t address);
extern void w25q16_page_write(uint32_t address, unsigned int lenth, unsigned char *string);
extern void w25q16_write_pro(uint32_t address, unsigned int lenth, unsigned char *string);
extern void w25q16_read_data(uint32_t address, unsigned int lenth);
extern void w25q16_read_datas(uint32_t address, unsigned int lenth, unsigned char *w25q16_datas);

#endif

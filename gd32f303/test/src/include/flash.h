
#ifndef __FLASH_H__
#define __FLASH_H__

#include <stdbool.h>
#include "gd32f30x.h"

#include <stdarg.h>
#include "string.h"
#include "systick.h"

// 10K Bytes
#define TXT_START_ADDRESS ((uint32_t)0x0807D800)
#define TXT_END_ADDRESS   ((uint32_t)0x08080000)

// 2K/Page
#define FMC_PAGE_SIZE     ((uint16_t)0x800U)
// 2K/Page, once write two bytes so size is 0x400
#define FLASH_PAGE_SIZE   ((uint16_t)0x400) //2048

extern void fmc_erase_pages(uint32_t address, uint32_t pages);
extern void fmc_write(uint32_t address, uint32_t size, uint16_t * data);
extern void fmc_read(uint32_t fmc_write_start_addr, uint32_t fmc_write_end_addr, uint32_t * data);
extern void flash_read_protection(unsigned char onoff);

#endif

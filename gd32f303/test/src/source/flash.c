
#include "flash.h"
#include "usart.h"

void fmc_erase_pages(uint32_t address, uint32_t pages)
{
    __disable_irq();
    fmc_unlock();

    fmc_flag_clear(FMC_FLAG_BANK0_END);
    fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
    fmc_flag_clear(FMC_FLAG_BANK0_PGERR);

    for (uint32_t pages = 0; pages < pages; pages++) {
        fmc_page_erase(address + (pages * FMC_PAGE_SIZE));

        fmc_flag_clear(FMC_FLAG_BANK0_END);
        fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
        fmc_flag_clear(FMC_FLAG_BANK0_PGERR);
    }

    fmc_lock();
    __enable_irq();
}

void fmc_write(uint32_t address, uint32_t size, uint16_t * data)
{
    uint32_t addr_t = 0;
    uint32_t i = 0;

    __disable_irq();
    fmc_unlock();

    addr_t = address;

    while (size > 0) {
        fmc_halfword_program(addr_t, data[i]);

        /**
         * 1 flash storage unit,
         * only storage 8bit data,
         * so 16 bit data need 2 unit
         * ┌─────────────┐
         * │ 8bit │ 8bit │
         * └─────────────┘
         */
        addr_t = addr_t + 2;
        i++;

        fmc_flag_clear(FMC_FLAG_BANK0_END);
        fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
        fmc_flag_clear(FMC_FLAG_BANK0_PGERR);

        size--;
    }

    fmc_lock();
    __enable_irq();
}

void fmc_read(uint32_t fmc_write_start_addr, uint32_t fmc_write_end_addr, uint32_t * data)
{
    int i = 0;
    uint32_t * address;

    __disable_irq();
    /**
     * uint32_t read_num = ((fmc_write_end_addr - fmc_write_start_addr) >> 2); 
     * Equivalent to dividing by 4
     */
    uint32_t read_num = (fmc_write_end_addr - fmc_write_start_addr) / 4;
 
    address = (uint32_t *)fmc_write_start_addr;

    for (i = 0; i < read_num; i++) {
        data[i] = *address;
        address++;
    }
    __enable_irq();
}

void flash_read_protection(unsigned char onoff)
{
    fmc_unlock();
    ob_unlock();

    /**
     * Disable read protection will clear flash
     */
    if (!onoff) {
        ob_security_protection_config(0xa5);
    } else {
        ob_security_protection_config(OB_SPC_SPC);
    }
}

/**
 * uint32_t flash_content[64] = {12345, 23456, 34567};
 *
 * [4]: (Write quantity)
 * fmc_erase_pages(TXT_START_ADDR, TXT_START_ADDR + 4);
 *
 * [16]: [Write quantity] * 4 -> (4x4)
 * fmc_program(TXT_START_ADDR, TXT_START_ADDR + 16, flash_content);
 *
 * [16]: [Read quantity] * 4  -> (4x4)
 * fmc_read(TXT_START_ADDR, TXT_START_ADDR + 16, flash_content);
 * uprint("%d\n", flash_content[0]);
 */

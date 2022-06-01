
#ifndef __GD25Q64_H__
#define __GD25Q64_H__

#include "gd25q64_spi.h"

#define WRITE      0x02 /* write to memory instruction */
#define WRSR       0x01 /* write status register instruction */
#define WREN       0x06 /* write enable instruction */

#define READ       0x03 /* read from memory instruction */
#define RDSR       0x05 /* read status register instruction  */
#define RDID       0x9F /* read identification */
#define SE         0x20 /* sector erase instruction */
#define SE2        0xD8 /* sector erase instruction */

#define BE         0xC7 /* bulk erase instruction */

#define WIP_FLAG   0x01 /* write in progress(wip)flag */
#define DUMMY_BYTE 0xA5

#define SFLASH_ID  0xc84017
#define PAGE_SIZE  0x100 /* 256 */
// GDW25Q64 SPI 高位先发送

extern unsigned int gd25q64_read_id();
static void gd25q64_write_enable();
static void tesing_gd25q64_busy();
extern void gd25q64_sector_erase(uint32_t sector_address);
extern void gd25q64_bulk_erase();
extern void gd25q64_page_write(uint32_t address, unsigned int lenth, unsigned char * data_buf);
extern unsigned char gd25q64_read_byte();
extern void gd25q64_buffer_write(uint32_t address, unsigned int lenth, unsigned char * data_buf);
extern void gd2564_buffer_read(uint32_t address, unsigned int lenth, unsigned char * data_buf);

#endif

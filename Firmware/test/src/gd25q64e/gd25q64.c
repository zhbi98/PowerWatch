
#include "gd25q64.h"

unsigned int gd25q64_read_id()
{
    unsigned int temp = 0, temp0 = 0, temp1 = 0, temp2 = 0;

    GD25Q64_CS_L();

    gd25q64_spi_write_read_byte(RDID);
    temp0 = gd25q64_spi_write_read_byte(DUMMY_BYTE);
    temp1 = gd25q64_spi_write_read_byte(DUMMY_BYTE);
    temp2 = gd25q64_spi_write_read_byte(DUMMY_BYTE);

    GD25Q64_CS_H();

    temp = (temp0 << 16) | (temp1 << 8) | temp2;
    return temp;
}

static void gd25q64_write_enable()
{
    GD25Q64_CS_L();
    gd25q64_spi_write_read_byte(WREN);
    GD25Q64_CS_H();
}

static void tesing_gd25q64_busy()
{
    unsigned char gd25q64_status = 0;

    GD25Q64_CS_L();

    gd25q64_spi_write_read_byte(RDSR);
    do {
        gd25q64_status = gd25q64_spi_write_read_byte(DUMMY_BYTE);
    } while ((gd25q64_status & 0x01) == SET);

    GD25Q64_CS_H();
}

void gd25q64_sector_erase(uint32_t sector_address)
{
    gd25q64_write_enable();

    GD25Q64_CS_L();

    gd25q64_spi_write_read_byte(SE);
    gd25q64_spi_write_read_byte((sector_address & 0xFF0000) >> 16);
    gd25q64_spi_write_read_byte((sector_address & 0xFF00) >> 8);
    gd25q64_spi_write_read_byte(sector_address & 0xFF);

    GD25Q64_CS_H();

    tesing_gd25q64_busy();
}

void gd25q64_bulk_erase()
{
    gd25q64_write_enable();

    GD25Q64_CS_L();

    gd25q64_spi_write_read_byte(BE);

    GD25Q64_CS_H();

    tesing_gd25q64_busy();
}

void gd25q64_page_write(uint32_t address, unsigned int lenth, unsigned char * data_buf)
{
    unsigned int i = 0;

    gd25q64_write_enable();

    GD25Q64_CS_L();

    gd25q64_spi_write_read_byte(WRITE);

    gd25q64_spi_write_read_byte((address & 0xff0000) >> 16);
    gd25q64_spi_write_read_byte((address & 0xff00) >> 8);
    gd25q64_spi_write_read_byte(address & 0xff);

    // This will cause access errors
    // while ((lenth <= 255) && (data_buf[i] != '\0')) {
    //     gd25q64_spi_write_read_byte(data_buf[i]);
    //     i++;
    // }
    while (lenth--) {
        gd25q64_spi_write_read_byte(data_buf[i]);
        i++;
    }

    GD25Q64_CS_H();
    tesing_gd25q64_busy();
}

unsigned char gd25q64_read_byte()
{
    return (gd25q64_spi_write_read_byte(DUMMY_BYTE));
}

void gd25q64_buffer_write(uint32_t address, unsigned int lenth, unsigned char * data_buf)
{
    unsigned char over_address = 0;
    unsigned char less_byte = 0;
    unsigned char pages = 0;
    unsigned char less_page = 0;
    unsigned char less;

    // Note: an address is a byte

    over_address = address % 256;
    less_byte    = 256 - over_address;
    pages        = lenth / 256;
    less_page    = lenth % 256;

    if (over_address == 0) {
        if (pages == 0) {
            gd25q64_page_write(address, lenth, data_buf);
        } else {
            for (; pages > 0; pages--) {
                gd25q64_page_write(address, 256, data_buf);
                address = address + 256;
                data_buf = data_buf + 256;
            }
            gd25q64_page_write(address, less_page, data_buf);
        }
    } else {
        if (pages == 0) {
            if (less_byte < less_page) {
                less = less_page - less_byte;
                gd25q64_page_write(address, less_byte, data_buf);
                address = address + less_byte;
                data_buf = data_buf + less_byte;
                gd25q64_page_write(address, less, data_buf);
            } else {
                gd25q64_page_write(address, lenth, data_buf);
            }
        } else {
            lenth = lenth - less_byte;
            pages = lenth / 256;
            less_page = lenth % 256;
            gd25q64_page_write(address, less_byte, data_buf);
            address = address + less_byte;
            data_buf = data_buf + less_byte;

            for (; pages > 0; pages--) {
                gd25q64_page_write(address, 256, data_buf);
                address = address + 256;
                data_buf = data_buf + 256;
            }

            if (less_page != 0) {
                gd25q64_page_write(address, less_page, data_buf);
            }
        }
    }
}

void gd25q64_buffer_read(uint32_t address, unsigned int lenth, unsigned char * data_buf)
{
    unsigned int read;

    GD25Q64_CS_L();

    gd25q64_spi_write_read_byte(READ);

    gd25q64_spi_write_read_byte((address & 0xff0000) >> 16);
    gd25q64_spi_write_read_byte((address & 0xff00) >> 8);
    gd25q64_spi_write_read_byte(address & 0xff);

    for (read = 0; read < lenth; read++) {
        *data_buf = gd25q64_spi_write_read_byte(DUMMY_BYTE);
        data_buf++;
    }

    GD25Q64_CS_H();
}

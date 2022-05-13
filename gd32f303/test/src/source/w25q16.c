
#include "w25q16.h"

unsigned char w25q16_data[32] = {0};

static void w25q16_gpio_init()
{
    rcu_periph_clock_enable(W25Q16_MISO_CLOCK);
    // rcu_periph_clock_enable(W25Q16_MOSI_CLOCK);
    // rcu_periph_clock_enable(W25Q16_SCLK_CLOCK);
    // rcu_periph_clock_enable(W25Q16_CS_CLOCK);

    gpio_init(W25Q16_SCLK_GPIO, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, W25Q16_SCLK_PIN);
    gpio_init(W25Q16_MOSI_GPIO, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, W25Q16_MOSI_PIN);

    gpio_init(W25Q16_MISO_GPIO, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, W25Q16_MISO_PIN);

    gpio_init(W25Q16_CS_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, W25Q16_CS_PIN);

    W25Q16_CS_H();
}

void w25q16_spibus_init()
{
    spi_parameter_struct spi_init_struct;

    w25q16_gpio_init();

    rcu_periph_clock_enable(SPI_CLOCK);

    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.prescale             = SPI_PSC_8;
    spi_init_struct.endian               = SPI_ENDIAN_MSB;
    spi_init(CURRENT_SPI, &spi_init_struct);

    spi_crc_polynomial_set(CURRENT_SPI, 7);
    spi_enable(CURRENT_SPI);
}

static unsigned char w25q16_send_byte(unsigned char a_byte)
{
    unsigned char timeout = 10;

    while (spi_i2s_flag_get(CURRENT_SPI, SPI_FLAG_TBE) == RESET) {
        if ((timeout--) == 0)
            return 0;
    }

    spi_i2s_data_transmit(CURRENT_SPI, a_byte);

    timeout = 10;

    while (spi_i2s_flag_get(CURRENT_SPI, I2S_FLAG_TRANS) == SET) {
        if ((timeout--) == 0)
            return 0;
    }

    return (spi_i2s_data_receive(CURRENT_SPI));
}

unsigned char w25q16_receive_byte()
{
    // return SPI_I2S_ReceiveData(CURRENT_SPI);
    return 0;
}

uint32_t read_w25q16_id()
{
    uint32_t id = 0, id1 = 0, id2 = 0, id3 = 0;

    W25Q16_CS_L();

    w25q16_send_byte(JEDEC_DEVICE_ID);

    id1 = w25q16_send_byte(DUMMY_BYTE);

    id2 = w25q16_send_byte(DUMMY_BYTE);

    id3 = w25q16_send_byte(DUMMY_BYTE);

    W25Q16_CS_H();

    id = (id1 << 16) | (id2 << 8) | id3;

    return id;
}

static void w25q16_write_enable()
{
    W25Q16_CS_L();
    w25q16_send_byte(WRITE_ENABLE);
    sleep_us(1);
    W25Q16_CS_H();
}

static void tesing_w25q16_busy()
{
    unsigned char w25q16_status = 0;

    W25Q16_CS_L();

    w25q16_send_byte(READ_STATUS);
    do {
        w25q16_status = w25q16_send_byte(DUMMY_BYTE);
    } while ((w25q16_status & 0x01) == SET);

    W25Q16_CS_H();
}

void w25q16_power_on()
{
    W25Q16_CS_L();

    w25q16_send_byte(RELEASE_POWEROFF);

    W25Q16_CS_H();
}

void w25q16_power_off()
{
    W25Q16_CS_L();

    w25q16_send_byte(POWER_OFF);

    W25Q16_CS_H();
}

void w25q16_sector_erase(uint32_t address)
{
    w25q16_write_enable();
    tesing_w25q16_busy();

    W25Q16_CS_L();

    w25q16_send_byte(SECTOR_ERASE);

    w25q16_send_byte((address & 0xff0000) >> 16);
    w25q16_send_byte((address & 0xff00) >> 8);
    w25q16_send_byte(address & 0xff);

    W25Q16_CS_H();
    tesing_w25q16_busy();
}

void w25q16_page_write(uint32_t address, unsigned int lenth, unsigned char *string)
{
    unsigned int i = 0;

    w25q16_write_enable();

    W25Q16_CS_L();

    w25q16_send_byte(PAGE_PROGRAM);

    w25q16_send_byte((address & 0xff0000) >> 16);
    w25q16_send_byte((address & 0xff00) >> 8);
    w25q16_send_byte(address & 0xff);

    // while ((lenth <= 255) && (string[i] != '\0')) {
    //     w25q16_send_byte(string[i]);
    //     i++;
    // }
    while (lenth--) {
        w25q16_send_byte(string[i]);
        i++;
    }

    W25Q16_CS_H();
    tesing_w25q16_busy();
}

void w25q16_write_pro(uint32_t address, unsigned int lenth, unsigned char *string)
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
            w25q16_page_write(address, lenth, string);
        } else {
            for (; pages > 0; pages--) {
                w25q16_page_write(address, 256, string);
                address = address + 256;
                string = string + 256;
            }
            w25q16_page_write(address, less_page, string);
        }
    } else {
        if (pages == 0) {
            if (less_byte < less_page) {
                less = less_page - less_byte;
                w25q16_page_write(address, less_byte, string);
                address = address + less_byte;
                string = string + less_byte;
                w25q16_page_write(address, less, string);
            } else {
                w25q16_page_write(address, lenth, string);
            }
        } else {
            lenth = lenth - less_byte;
            pages = lenth / 256;
            less_page = lenth % 256;
            w25q16_page_write(address, less_byte, string);
            address = address + less_byte;
            string = string + less_byte;

            for (; pages > 0; pages--) {
                w25q16_page_write(address, 256, string);
                address = address + 256;
                string = string + 256;
            }

            if (less_page != 0) {
                w25q16_page_write(address, less_page, string);
            }
        }
    }
}

void w25q16_read_data(uint32_t address, unsigned int lenth)
{
    unsigned int read;

    W25Q16_CS_L();

    w25q16_send_byte(READ_DATA);

    w25q16_send_byte((address & 0xff0000) >> 16);
    w25q16_send_byte((address & 0xff00) >> 8);
    w25q16_send_byte(address & 0xff);

    for (read = 0; read < lenth; read++) {
        w25q16_data[read] = w25q16_send_byte(DUMMY_BYTE);
    }

    W25Q16_CS_H();
}

void w25q16_read_datas(uint32_t address, unsigned int lenth, unsigned char *w25q16_datas)
{
    unsigned int read;

    W25Q16_CS_L();

    w25q16_send_byte(READ_DATA);

    w25q16_send_byte((address & 0xff0000) >> 16);
    w25q16_send_byte((address & 0xff00) >> 8);
    w25q16_send_byte(address & 0xff);

    for (read = 0; read < lenth; read++) {
        *w25q16_datas = w25q16_send_byte(DUMMY_BYTE);
        w25q16_datas++;
    }

    W25Q16_CS_H();
}

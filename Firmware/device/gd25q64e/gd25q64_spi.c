
#include "gd25q64_spi.h"

static void gd25q64_sleep_us(unsigned int us)
{
    unsigned int i;

    /**
     * precise delay is best for software spi bus, but
     * how to determine if the delay is accurate?
     *
     * IO can be set to output mode, so output a 
     * square wave through this IO, and then use an 
     * oscilloscope to measure the period of the 
     * square wave to know.
     * 
     * Example:
     * MCU_IO_OUTPUT_H();
     * delay_us(2);
     * MCU_IO_OUTPUT_L();
     * delay_us(2);
     */
    for (; us > 0; us--)
        for (i = 20; i > 0; i--);
}

void gd25q64_spi_gpio_init()
{
    rcu_periph_clock_enable(GD25Q64_CS_CLOCK);
    rcu_periph_clock_enable(GD25Q64_SCLK_CLOCK);
    rcu_periph_clock_enable(GD25Q64_MOSI_CLOCK);
    rcu_periph_clock_enable(GD25Q64_MISO_CLOCK);

    gpio_init(GD25Q64_CS_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GD25Q64_CS_PIN);
    gpio_init(GD25Q64_SCLK_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GD25Q64_SCLK_PIN);
    gpio_init(GD25Q64_MOSI_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GD25Q64_MOSI_PIN);
    gpio_init(GD25Q64_MISO_GPIO, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GD25Q64_MISO_PIN);

    GD25Q64_CS_H();
    GD25Q64_SCLK_L();
    GD25Q64_MOSI_H();
    GD25Q64_MISO_H();
}

void gd25q64_spi_send_byte(unsigned char byte)
{
    unsigned char i = 0;
    unsigned char temp = 0;

    for (i = 0; i < 8; i++) {
        temp = ((byte & 0x80) == 0x80) ? 1 : 0;
        byte = byte << 1;
        GD25Q64_SCLK_L();    // SPI_CLK(0); // CPOL=0
        
        // SPI_MOSI(temp);
        if (temp)
            GD25Q64_MOSI_H();
        else
            GD25Q64_MOSI_L();

        gd25q64_sleep_us(4); // SPI_Delay();
        GD25Q64_SCLK_H();    // SPI_CLK(1); // CPHA=0
        gd25q64_sleep_us(4); // SPI_Delay();
    }
    GD25Q64_SCLK_L();        // SPI_CLK(0);
}

unsigned char gd25q64_spi_read_byte()
{
    unsigned char i = 0;
    unsigned char read_data = 0xFF;

    for (i = 0; i < 8; i++) {
        read_data = read_data << 1;
        GD25Q64_SCLK_L();    // SPI_CLK(0);
        gd25q64_sleep_us(4); // SPI_Delay();
        GD25Q64_SCLK_H();    // SPI_CLK(1);
        gd25q64_sleep_us(4); // SPI_Delay();

        if (READ_GD25Q64_MISO() == 1 /*SPI_MISO()==1*/) {
            read_data = read_data + 1;
        }
    }
    GD25Q64_SCLK_L();        // SPI_CLK(0);
    return read_data;
}

unsigned char gd25q64_spi_write_read_byte(unsigned char data)
{
    unsigned char i = 0;
    unsigned char temp = 0;
    unsigned char read_data = 0xFF;

    for (i = 0; i < 8; i++) {
        temp = ((data & 0x80) == 0x80) ? 1 : 0;
        data = data<<1;
        read_data = read_data<<1;
        GD25Q64_SCLK_L();    // SPI_CLK(0);

        // SPI_MOSI(temp);
        if (temp)
            GD25Q64_MOSI_H();
        else
            GD25Q64_MOSI_L();

        gd25q64_sleep_us(4); // SPI_Delay();
        GD25Q64_SCLK_H();    // SPI_CLK(1);
        gd25q64_sleep_us(4); // SPI_Delay();

        if (READ_GD25Q64_MISO() == 1 /*SPI_MISO()==1*/) {
            read_data = read_data + 1; 
        }
    }
    GD25Q64_SCLK_L();        // SPI_CLK(0);
    return read_data;
}

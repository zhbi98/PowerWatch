
#include "st7789.h"

void st7789_gpio_init()
{
    rcu_periph_clock_enable(ST7789_RST_CLOCK);
    rcu_periph_clock_enable(ST7789_CS_CLOCK);
    rcu_periph_clock_enable(ST7789_DC_CLOCK);
    rcu_periph_clock_enable(ST7789_WR_CLOCK);
    rcu_periph_clock_enable(ST7789_RD_CLOCK);

    rcu_periph_clock_enable(ST7789_D0_CLOCK);
    rcu_periph_clock_enable(ST7789_D1_CLOCK);
    rcu_periph_clock_enable(ST7789_D2_CLOCK);
    rcu_periph_clock_enable(ST7789_D3_CLOCK);
    rcu_periph_clock_enable(ST7789_D4_CLOCK);
    rcu_periph_clock_enable(ST7789_D5_CLOCK);
    rcu_periph_clock_enable(ST7789_D6_CLOCK);
    rcu_periph_clock_enable(ST7789_D7_CLOCK);

    rcu_periph_clock_enable(RCU_AF);

    gpio_init(ST7789_RST_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_RST_PIN);
    gpio_init(ST7789_CS_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_CS_PIN);
    gpio_init(ST7789_DC_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_DC_PIN);
    gpio_init(ST7789_WR_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_WR_PIN);
    gpio_init(ST7789_RD_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_RD_PIN);
    
    gpio_init(ST7789_D0_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_D0_PIN);
    gpio_init(ST7789_D1_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_D1_PIN);
    gpio_init(ST7789_D2_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_D2_PIN);
    gpio_init(ST7789_D3_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_D3_PIN);
    gpio_init(ST7789_D4_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_D4_PIN);
    gpio_init(ST7789_D5_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_D5_PIN);
    gpio_init(ST7789_D6_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_D6_PIN);
    gpio_init(ST7789_D7_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_D7_PIN);

    // ST7789_RST_H();
    // ST7789_CS_H();
    // ST7789_DC_H();
    // ST7789_WR_H();
    // ST7789_RD_H();

    // ST7789_D0_SET(1);
    // ST7789_D1_SET(1);
    // ST7789_D2_SET(1);
    // ST7789_D3_SET(1);
    // ST7789_D4_SET(1);
    // ST7789_D5_SET(1);
    // ST7789_D6_SET(1);
    // ST7789_D7_SET(1);
}

void st7789_bus(unsigned char data)
{
    // ST7789_CS_L();

    // 8421, 8421
    ST7789_D0_SET((data & 0x01) >> 0);
    ST7789_D1_SET((data & 0x02) >> 1);
    ST7789_D2_SET((data & 0x04) >> 2);
    ST7789_D3_SET((data & 0x08) >> 3);
    ST7789_D4_SET((data & 0x10) >> 4);
    ST7789_D5_SET((data & 0x20) >> 5);
    ST7789_D6_SET((data & 0x40) >> 6);
    ST7789_D7_SET((data & 0x80) >> 7);

    // ST7789_WR_L();
    // ST7789_WR_H();

    // ST7789_CS_H();
}

void write_command(unsigned char command)
{
    ST7789_CS_L();
    // ------------------------
    ST7789_DC_L();

    st7789_bus(command);
    // ------------------------
    ST7789_WR_L();
    ST7789_WR_H();

    ST7789_CS_H();
}

void write_data(unsigned char data)
{
    ST7789_CS_L();
    // ------------------------
    ST7789_DC_H();
    
    st7789_bus(data);
    // ------------------------
    ST7789_WR_L();
    ST7789_WR_H();

    ST7789_CS_H();
}

void write_datas(unsigned int data)
{
    ST7789_CS_L();
    // ------------------------
    ST7789_DC_H();

    st7789_bus(data >> 8);
    st7789_bus(data);
    // ------------------------
    ST7789_WR_L();
    ST7789_WR_H();

    ST7789_CS_H();
}

void st7789_reset()
{
    ST7789_RST_H();
    sleep_ms(100);
    ST7789_RST_L();
    sleep_ms(100);
    ST7789_RST_H();
    sleep_ms(100);
}

void st7789_direction(unsigned char direction)
{
    write_command(0x36);

    switch (direction) {
        // +----- x 
        // |
        // |
        // y
        case 0 : write_data(0xa8); break;
        // y -----+
        //        |
        //        |
        //        x
        case 1 : write_data(0x08); break;
        //        y
        //        |
        //        |
        // x -----+
        case 2 : write_data(0x68); break;
        // x
        // |
        // |
        // +----- y
        case 3 : write_data(0xc8); break;
    }
}

void st7789_init()
{
    st7789_gpio_init();

    st7789_reset();

    write_command(0x11);

    write_command(0x3A);
    write_data(/*0x05*/0x65);

    write_command(0xB2);
    write_data(0x0C);
    write_data(0x0C);
    write_data(0x00);
    write_data(0x33);
    write_data(0x33); 

    write_command(0xB7); 
    write_data(0x35);  

    write_command(0xBB);
    write_data(0x1A);

    write_command(0xC0);
    write_data(0x2C);

    write_command(0xC2);
    write_data(0x01);

    write_command(0xC3);
    write_data(0x0B);   

    write_command(0xC4);
    write_data(0x20);  

    write_command(0xC6); 
    write_data(0x0F);    

    write_command(0xD0); 
    write_data(0xA4);
    write_data(0xA1);

    write_command(0x21); 
    write_command(0xE0);
    write_data(0xF0);
    write_data(0x00);
    write_data(0x04);
    write_data(0x04);
    write_data(0x04);
    write_data(0x05);
    write_data(0x29);
    write_data(0x33);
    write_data(0x3E);
    write_data(0x38);
    write_data(0x12);
    write_data(0x12);
    write_data(0x28);
    write_data(0x30);

    write_command(0xE1);
    write_data(0xF0);
    write_data(0x07);
    write_data(0x0A);
    write_data(0x0D);
    write_data(0x0B);
    write_data(0x07);
    write_data(0x28);
    write_data(0x33);
    write_data(0x3E);
    write_data(0x36);
    write_data(0x14);
    write_data(0x14);
    write_data(0x29);
    write_data(0x32);

    st7789_direction(2);

    write_command(0x11);
    sleep_ms(200);  
    write_command(0x29);

    tft_clear(0xffff);
}

void display_position(unsigned int y, unsigned int x)
{
    unsigned char seting_x = 0x2a;
    unsigned char seting_y = 0x2b;

    write_command(seting_x);
    write_datas(x >> 8);
    write_datas(0x00ff & x);
    write_datas((x + 1) >> 8);
    write_datas((x + 1));
    
    write_command(seting_y);
    write_datas(y >> 8);
    write_datas(0x00ff & y);
    write_datas((y + 1) >> 8);
    write_datas((y + 1));

    // display pixel
    write_command(0x2c);
}

void display_region(unsigned int y, unsigned int x, unsigned int width, unsigned int height)
{
    write_command(0x2a);
    write_datas(x >> 8);
    write_datas(x & 0xff);
    write_datas((x + width - 1) >> 8);
    write_datas((x + width - 1) & 0xff);

    write_command(0x2b);
    write_datas(y >> 8);
    write_datas(y & 0xff);
    write_datas((y + height - 1) >> 8);
    write_datas((y + height - 1) & 0xff);

    write_command(0x2c);
}

void display_pixel(unsigned int y, unsigned int x, unsigned int color)
{
    display_position(y, x);
    write_datas(color);
}

void tft_clear(unsigned int color)
{
    unsigned int x;
    unsigned int y;

    for (y = 1; y < TFT_HEIGHT; y++) {
        for (x = 1; x < TFT_WIDTH; x++) {
            display_pixel(y, x, color);
        }
    }
}

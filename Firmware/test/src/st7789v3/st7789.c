
#include "st7789.h"

void st7789_gpio_init()
{
    rcu_periph_clock_enable(ST7789_BL_CLOCK);
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

    // rcu_periph_clock_enable(RCU_AF);

    gpio_init(ST7789_BL_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, ST7789_BL_PIN);
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

    ST7789_BL_L();
    ST7789_RST_H();
    ST7789_CS_H();
    ST7789_DC_H();
    ST7789_WR_H();
    ST7789_RD_H();
    ST7789_D0_H();
    ST7789_D1_H();
    ST7789_D2_H();
    ST7789_D3_H();
    ST7789_D4_H();
    ST7789_D5_H();
    ST7789_D6_H();
    ST7789_D7_H();
    sleep_ms(100);
}

void ST7789_DATA_OUT(unsigned char data)
{
    // 8421, 8421

    if (data & 0x80) {
        ST7789_D7_HH();
    } else {
        ST7789_D7_LL();
    }

    if (data & 0x40) {
        ST7789_D6_HH();
    } else {
        ST7789_D6_LL();
    }

    if (data & 0x20) {
        ST7789_D5_HH();
    } else {
        ST7789_D5_LL();
    }

    if (data & 0x10) {
        ST7789_D4_HH();
    } else {
        ST7789_D4_LL();
    }

    if(data & 0x08) {
        ST7789_D3_HH();
    } else {
        ST7789_D3_LL();
    }

    if (data & 0x04) {
        ST7789_D2_HH();
    } else {
        ST7789_D2_LL();
    }

    if(data & 0x02) {
        ST7789_D1_HH();
    } else {
        ST7789_D1_LL();
    }

    if(data & 0x01) {
        ST7789_D0_HH();
    } else {
        ST7789_D0_LL();
    }
}

void st7789_write_bus(unsigned char data)
{
    ST7789_CS_LL();
    ST7789_WR_LL();

    ST7789_DATA_OUT(data);

    ST7789_WR_HH();
    ST7789_CS_HH();
}

void write_command(unsigned char command)
{
    ST7789_DC_LL();
    st7789_write_bus(command);
    ST7789_DC_HH();
}

void write_data(unsigned char data)
{
    st7789_write_bus(data);
}

void write_datas(unsigned short data)
{
    st7789_write_bus(data >> 8);
    st7789_write_bus(data);
}

void st7789_reset()
{
    ST7789_RST_L();
    sleep_ms(100);
    ST7789_RST_H();
    sleep_ms(100);
}

void st7789_dir(unsigned char dir)
{
    write_command(0x36);

    /**
     * The screen coordinate system is as follows:
     * +----- x 
     * |
     * |
     * y
     *
     * We can specify by ourselves that the vertical screen 
     * direction when the FPC cable is down is used as the reference direction.
     * Adjust the screen orientation value so that the screen coordinate system 
     * conforms to our self-defined reference orientation,
     * The screen orientation value at this time is the screen orientation 
     * value of the reference orientation.
     *
     * Rotate the screen coordinate system in the reference direction 
     * clockwise or counterclockwise to get the rotated screen
     * The screen coordinate system, because the screen display 
     * must be refreshed to the right along the X axis, and refreshed 
     * downward along the Y axis
     * So you can know the refresh direction of the screen after rotation.
     *
     * The four orientation values correspond to two landscape orientations 
     * and two portrait orientations.
     */
    switch (dir) {
        // +----- x
        // |
        // |
        // y
        case 0 : write_data(0x00); break;
        // y -----+
        //        |
        //        |
        //        x
        case 1 : write_data(0x70); break;
        //        y
        //        |
        //        |
        // x -----+
        case 2 : write_data(0xc0); break;
        // x
        // |
        // |
        // +----- y
        case 3 : write_data(0xa0); break;
    }
}

void st7789_init()
{
    // LCD MicroController ST7789V3
    st7789_gpio_init();
    st7789_reset();
    ST7789_BL_L();
    sleep_ms(100);

    write_command(0x11);
    sleep_ms(120);
    st7789_dir(TFT_DIR);

    write_command(0x3a);
    write_data(0x05);

    write_command(0xb2);
    write_data(0x0c);
    write_data(0x0c);
    write_data(0x00);
    write_data(0x33);
    write_data(0x33);

    write_command(0xb7);
    write_data(0x35);

    write_command(0xbb);
    write_data(0x1a);

    write_command(0xc0);
    write_data(0x2c);

    write_command(0xc2);
    write_data(0x01);

    write_command(0xc3);
    write_data(0x0b);

    write_command(0xc4);
    write_data(0x20);

    write_command(0xc6);
    write_data(0x0f);

    write_command(0xd0);
    write_data(0xa4);
    write_data(0xa1);

    write_command(0x21);
    write_command(0xe0);
    write_data(0xf0);
    write_data(0x00);
    write_data(0x04);
    write_data(0x04);
    write_data(0x04);
    write_data(0x05);
    write_data(0x29);
    write_data(0x33);
    write_data(0x3e);
    write_data(0x38);
    write_data(0x12);
    write_data(0x12);
    write_data(0x28);
    write_data(0x30);

    write_command(0xe1);
    write_data(0xf0);
    write_data(0x07);
    write_data(0x0a);
    write_data(0x0d);
    write_data(0x0b);
    write_data(0x07);
    write_data(0x28);
    write_data(0x33);
    write_data(0x3e);
    write_data(0x36);
    write_data(0x14);
    write_data(0x14);
    write_data(0x29);
    write_data(0x32);

    write_command(0x11);
    sleep_ms(120);
    write_command(0x29);
    clear(0x0000);
}

void display_region(unsigned short y, unsigned short x, unsigned short width, unsigned short height)
{
    switch (TFT_DIR) {
    case 0:
        write_command(0x2a);
        write_datas(x + 35);
        write_datas(x + (width - 1) + 35);

        write_command(0x2b);
        write_datas(y);
        write_datas(y + (height - 1));
        break;
    case 1:
        write_command(0x2a);
        write_datas(x);
        write_datas(x + (width - 1));

        write_command(0x2b);
        write_datas(y + 35);
        write_datas(y + (height - 1) + 35);
        break;
    case 2:
        write_command(0x2a);
        write_datas(x + 35);
        write_datas(x + (width - 1) + 35);

        write_command(0x2b);
        write_datas(y);
        write_datas(y + (height - 1));
        break;
    case 3:
        write_command(0x2a);
        write_datas(x);
        write_datas(x + (width - 1));

        write_command(0x2b);
        write_datas(y + 35);
        write_datas(y + (height - 1) + 35);
        break;
    }
    write_command(0x2c);
}

void clear(unsigned short color)
{          
    unsigned short pix_num = TFT_WIDTH * TFT_HEIGHT;

    display_region(0, 0, TFT_WIDTH, TFT_HEIGHT);
    for (; pix_num > 0; pix_num--) {
        write_datas(color);
    }
}

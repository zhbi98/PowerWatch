
#include "ina226_i2c.h"

static void ina226_sleep_us(unsigned int us)
{
    volatile unsigned int i = 0;

    /**
     * precise delay is best for software i2c bus, but
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

void ina226_gpio_init()
{
    rcu_periph_clock_enable(INA226_SDA_CLOCK);
    /*rcu_periph_clock_enable(INA226_SCL_CLOCK);*/

    /*Output OD requires a pull-up resistor*/
    /*gpio_init(INA226_SDA_GPIO, GPIO_MODE_OUT_OD, GPIO_OSPEED_50MHZ, INA226_SDA_PIN);*/
    gpio_init(INA226_SDA_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, INA226_SDA_PIN);
    gpio_init(INA226_SCL_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, INA226_SCL_PIN);

    ina226_sda_out_mode();
    INA226_SDA_H();
}

void ina226_sda_out_mode()
{
    gpio_init(INA226_SDA_GPIO, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, INA226_SDA_PIN);
}

void ina226_sda_in_mode()
{
    gpio_init(INA226_SDA_GPIO, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, INA226_SDA_PIN);
}

void ina226_i2c_start()
{
    ina226_sda_out_mode();
    INA226_SDA_H();
    INA226_SCL_H();
    ina226_sleep_us(4);
    INA226_SDA_L();
    ina226_sleep_us(4);
    INA226_SCL_L();
}

void ina226_i2c_stop()
{
    ina226_sda_out_mode();
    INA226_SCL_L();
    INA226_SDA_L();
    ina226_sleep_us(4);
    INA226_SCL_H();
    ina226_sleep_us(1);
    INA226_SDA_H();
    ina226_sleep_us(4);
}

unsigned char ina226_i2c_wait_ack()
{
    unsigned char times = 0;

    ina226_sda_in_mode();
    INA226_SDA_H();
    ina226_sleep_us(1);     
    INA226_SCL_H();
    ina226_sleep_us(1); 

    while (READ_INA226_SDA()) {
        // times++;
        if (times > 255) {
            ina226_i2c_stop();
            INA226_SCL_L();
            return 1;
        }
    }
    INA226_SCL_L();
    return 0;  
}

void ina226_i2c_ack()
{
    INA226_SCL_L();
    ina226_sda_out_mode();
    INA226_SDA_L();
    ina226_sleep_us(2);
    INA226_SCL_H();
    ina226_sleep_us(2);
    INA226_SCL_L();
}

void ina226_i2c_nack()
{
    INA226_SCL_L();
    ina226_sda_out_mode();
    INA226_SDA_H();
    ina226_sleep_us(2);
    INA226_SCL_H();
    ina226_sleep_us(2);
    INA226_SCL_L();
}

void ina226_i2c_send_byte(unsigned char a_byte)
{                        
    unsigned char send;

    ina226_sda_out_mode();
    INA226_SCL_L();
    for (send = 0; send < 8; send++) {              
        if ((a_byte & 0x80) >> 7)
            INA226_SDA_H();
        else
            INA226_SDA_L();
        a_byte <<= 1;
        ina226_sleep_us(2);
        INA226_SCL_H();
        ina226_sleep_us(2); 
        INA226_SCL_L();
        ina226_sleep_us(2);
    }    
} 

unsigned char ina226_i2c_read_byte(unsigned char ack)
{
    unsigned char i, receive = 0;

    ina226_sda_in_mode();
    for (i = 0; i < 8; i++) {
        INA226_SCL_L();
        ina226_sleep_us(2);
        INA226_SCL_H();
        receive <<= 1;
        if (READ_INA226_SDA())
            receive++;
        ina226_sleep_us(1); 
    }

    if (!ack)
        ina226_i2c_nack();
    else
        ina226_i2c_ack();
    return receive;
}

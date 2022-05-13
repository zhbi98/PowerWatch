
#include "usart.h"

static void usart_gpio_init()
{
    rcu_periph_clock_enable(USART_TX_CLOCK); // enable GPIO clock, PA9/PA10
    rcu_periph_clock_enable(USART_RX_CLOCK);
    rcu_periph_clock_enable(RCU_AF);

    gpio_init(USART_TX_GPIO, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, USART_TX_PIN); // PA9->TX0
    gpio_init(USART_RX_GPIO, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, USART_RX_PIN); // PA10->RX0
    // gpio_init(USART_RX_GPIO, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, USART_RX_PIN);
}

void usart_init()
{
    usart_gpio_init();
    nvic_irq_enable(USART_IRQN, 0, 0);
    rcu_periph_clock_enable(USART_CLOCK);

    // USART0: 115200
    usart_deinit(CURRENT_USART);
    usart_baudrate_set(CURRENT_USART, BAUD_RATE);
    usart_word_length_set(CURRENT_USART, USART_WL_8BIT);
    usart_stop_bit_set(CURRENT_USART, USART_STB_1BIT);
    usart_parity_config(CURRENT_USART, USART_PM_NONE);
    usart_hardware_flow_rts_config(CURRENT_USART, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(CURRENT_USART, USART_CTS_DISABLE);
    usart_receive_config(CURRENT_USART, USART_RECEIVE_ENABLE);
    usart_transmit_config(CURRENT_USART, USART_TRANSMIT_ENABLE);
    usart_enable(CURRENT_USART);
}

void usart_send_byte(unsigned char a_byte)
{
    usart_data_transmit(CURRENT_USART, a_byte);
    while (usart_flag_get(CURRENT_USART, USART_FLAG_TBE) == RESET);
}

void usart_send_string(const unsigned char * string)
{
    unsigned int i = 0;

    while (string[i] != '\0') {
        usart_send_byte(string[i]);
        i++;
    }
}

void usart_send_fmt_string(unsigned char * format, ...)
{
    unsigned char value[128];

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    usart_send_string(value);
}

static struct usart_buf_t usart_buf;

void USART_IRQHANDLER()
{
    unsigned char byte = '\0';

    if (usart_interrupt_flag_get(CURRENT_USART, USART_INT_FLAG_RBNE) != RESET) {
        byte = usart_data_receive(CURRENT_USART);
        usart_buf.data[usart_buf.index] = byte;
        usart_buf.index++;
        if (usart_buf.index >= 128)
            usart_buf.index = 0;
    }
}

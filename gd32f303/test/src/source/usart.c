
#include "usart.h"

struct usart_buf_t usart_buf;

void usart_gpio_init()
{
    rcu_periph_clock_enable(USART_TX_CLOCK);
    rcu_periph_clock_enable(USART_RX_CLOCK);

    rcu_periph_clock_enable(RCU_AF);
    // TX: GPIOB->GPIO_PIN_10 remap to GPIOC->GPIO_PIN_10
    // RX: GPIOB->GPIO_PIN_11 remap to GPIOC->GPIO_PIN_11
    gpio_pin_remap_config(GPIO_USART2_PARTIAL_REMAP, ENABLE);

    gpio_init(USART_TX_GPIO, GPIO_MODE_AF_PP,       GPIO_OSPEED_50MHZ, USART_TX_PIN);
    gpio_init(USART_RX_GPIO, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, USART_RX_PIN);
}

void usart_init()
{
    usart_gpio_init();

    nvic_irq_enable(USART_IRQN, 0, 0);

    rcu_periph_clock_enable(USART_CLOCK);

    usart_deinit(USART);
    usart_baudrate_set(USART, USART_BRATE);
    usart_receive_config(USART, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART, USART_TRANSMIT_ENABLE);
    usart_enable(USART);
    usart_interrupt_enable(USART, USART_INT_RBNE);
}

void usart_send_byte(unsigned char a_byte)
{
    usart_data_transmit(USART, a_byte);
    while (usart_flag_get(USART, USART_FLAG_TBE) == RESET);
}

void usart_send_string(unsigned char * string)
{
    unsigned char i = 0;

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

void USART_IRQHANDLER()
{
    unsigned char data;

    if (usart_interrupt_flag_get(USART, USART_INT_FLAG_RBNE) != RESET) {
        data = usart_data_receive(USART);

        usart_buf.data[usart_buf.index] = data;
        usart_buf.index++;

        if (usart_buf.index > 64)
            usart_buf.index = 0;

        if ((data == '\n') || (data == '\r') || (data == ';')) {
            // Remove last one character ';' or '\n' and so on.
            usart_buf.data[usart_buf.index - 1] = 0;
            input_pool(&message_pool, usart_buf.data, usart_buf.index - 1);
            usart_buf.index = 0;
        }

        // usart_send_byte(data);
        usart_interrupt_flag_clear(USART, USART_INT_FLAG_RBNE);
    }
}

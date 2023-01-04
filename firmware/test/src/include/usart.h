
#ifndef __USART_H__
#define __USART_H__

#include <stdio.h>
#include <stdarg.h>
#include "gd32f10x.h"

#define CURRENT_USART USART0
#define BAUD_RATE     115200
#define USART_CLOCK   RCU_USART0

#define USART_TX_GPIO  GPIOA
#define USART_TX_PIN   GPIO_PIN_9
#define USART_TX_CLOCK RCU_GPIOA

#define USART_RX_GPIO  GPIOA
#define USART_RX_PIN   GPIO_PIN_10
#define USART_RX_CLOCK RCU_GPIOA

#define USART_IRQN         USART1_IRQn
#define USART_IRQHANDLER() USART1_IRQHandler()

struct usart_buf_t {
	unsigned int index;
	unsigned char data[64];
};

static struct usart_buf_t usart_buf;

static void usart_gpio_init();
extern void usart_init();
extern void usart_send_byte(unsigned char a_byte);
extern void usart_send_string(const unsigned char * string);
extern void usart_send_fmt_string(unsigned char * format, ...);
extern void USART_IRQHANDLER();

#endif

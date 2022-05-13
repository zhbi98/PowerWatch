
#include <stdio.h>

#include "gd32f30x.h"
#include "usart.h"
#include "time.h"
#include "log.h"

void remap_gpio_init()
{
    rcu_periph_clock_enable(RCU_AF);
    // gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);
    gpio_pin_remap_config(GPIO_SWJ_DISABLE_REMAP, ENABLE);
}

void test_gpio_init()
{
	rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_14);
}

int main()
{
    remap_gpio_init();
    test_gpio_init();
    usart_init();

    for (;;) {
    	info("Hello, World!");
        sleep_ms(1000);

		// gpio_bit_reset(GPIOA, GPIO_PIN_14);
		// sleep_ms(1000);
		// gpio_bit_set(GPIOA, GPIO_PIN_14);
		// sleep_ms(1000);
    }

    return 0;
}

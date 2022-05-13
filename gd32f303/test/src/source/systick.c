
#include "systick.h"

uint32_t sleep_t = 0;

void systick_config()
{
    // setup systick timer for 1000Hz interrupts
    if (SysTick_Config(SystemCoreClock / 1000U)) {
        // capture error
        while (1) {}
    }

    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

void delay_1ms(uint32_t ms)
{
    sleep_t = ms;
    while (sleep_t != 0);
}

void SysTick_Handler()
{
    static unsigned char t = 0;

    if (sleep_t != 0) {
        sleep_t--;
    }

    debug_led_twink();
}

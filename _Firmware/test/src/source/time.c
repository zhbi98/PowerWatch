
#include "time.h"

void sleep_us(unsigned int us)
{
    volatile unsigned int i;

    for (; us > 0; us--)
        for (i = 12; i > 0; i--);
}

void sleep_ms(unsigned int ms)
{
    volatile unsigned int i;

    for (; ms > 0; ms--)
        for (i = 12000; i > 0; i--);
}


#include "average.h"

struct average_calc_t average_calc = {
    .cache_size = 0,
    .sum = 0.0,
    .average = 0.0,
};

struct cache_buffer_t average_cache_buf;

void average_calc_hanlder(float value)
{
    cache_typedef cache_data;

    cache_input(&average_cache_buf, value);
    average_calc.cache_size++;

    for (unsigned char i = 0; i < average_calc.cache_size; i++) 
        average_calc.sum += average_cache_buf.buf[i];
    average_calc.average = average_calc.sum / average_calc.cache_size;
    average_calc.sum = 0;

    if (cache_full(&average_cache_buf)) {
        cache_output(&average_cache_buf, &cache_data);
        average_calc.cache_size--;
    }
}

void average_calc_reset()
{
    average_calc.cache_size = 0;
    cache_init(&average_cache_buf);
}

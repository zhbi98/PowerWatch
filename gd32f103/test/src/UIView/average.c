
#include "average.h"

struct average_calc_t average_calc = {
    .sum = 0.0,
    .avg = 0.0,
    .type = 0,
};

struct cache_buffer_t average_cache_buf;

void average_calc_hanlder()
{
    cache_typedef pool_data;

    if (cache_full(&average_cache_buf) == true) {
        cache_output(&average_cache_buf, &pool_data);
        cache_input(&average_cache_buf, ina226_data.Shunt_Current);

        for (char i = 0; i < 32; i++) {
            average_calc.sum = average_calc.sum + average_cache_buf.buf[i];
        }

        average_calc.avg = average_calc.sum / 32;
        average_calc.sum = 0;
    } else {
        cache_input(&average_cache_buf, ina226_data.Shunt_Current);
    }
}

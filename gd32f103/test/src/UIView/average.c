
#include "average.h"

Average average = {
    .sum = 0.0,
    .avg = 0.0,
    .type = 0,
};

struct cache_buffer_t avg_pool;

void electricalAverage()
{
    cache_typedef pool_data;

    if (cache_full(&avg_pool) == true) {
        cache_output(&avg_pool, &pool_data);
        cache_input(&avg_pool, ina226_data.Shunt_Current);

        for (char i = 0; i < 32; i++) {
            average.sum = average.sum + avg_pool.buf[i];
        }

        average.avg = average.sum / 32;
        average.sum = 0;
    } else {
        cache_input(&avg_pool, ina226_data.Shunt_Current);
    }
}

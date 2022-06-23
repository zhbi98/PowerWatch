
#include "average.h"

Average average = {
    .sum = 0.0,
    .avg = 0.0,
    .type = 0,
};

struct data_pool_t avg_pool;

void electricalAverage()
{
    pool_data_t pool_data;

    if (pool_full(&avg_pool) == true) {
        output_pool(&avg_pool, &pool_data);
        input_pool(&avg_pool, ina226_data.Shunt_Current);

        for (char i = 0; i < 32; i++) {
            average.sum = average.sum + avg_pool.buf[i];
        }

        average.avg = average.sum / 32;
        average.sum = 0;
    } else {
        input_pool(&avg_pool, ina226_data.Shunt_Current);
    }
}

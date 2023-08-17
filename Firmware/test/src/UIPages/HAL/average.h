
#ifndef __AVERAGE_H__
#define __AVERAGE_H__

#include <stdbool.h>
#include "ina226.h"
#include "cache.h"

struct average_calc_t {
    unsigned char cache_size;
    float sum;
    float average;
};

extern struct average_calc_t average_calc;
extern struct cache_buffer_t average_cache_buf;

extern void average_calc_hanlder(float value);
extern void average_calc_reset();

#endif

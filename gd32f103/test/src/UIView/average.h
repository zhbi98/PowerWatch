
#ifndef __AVERAGE_H__
#define __AVERAGE_H__

#include <stdbool.h>
#include "ina226.h"
#include "cache.h"

typedef struct {
    float sum;
    float avg;
    unsigned char type;
} Average;

extern Average average;
extern struct cache_buffer_t avg_pool;
extern void electricalEnergy();
extern void electricalAverage();

#endif

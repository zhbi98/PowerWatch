
#ifndef __DATA_POOL_H__
#define __DATA_POOL_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DATA_LEN 32
#define MAX_BUF_LEN  32

typedef float cache_typedef;

struct cache_buffer_t {
    unsigned char phead;
    unsigned char ptail;
    cache_typedef buf[MAX_BUF_LEN];
};

/**
 * example:
 * struct cache_buffer_t cache_buffer;
 */

extern void cache_init(struct cache_buffer_t * cache);
extern unsigned char cache_empty(struct cache_buffer_t * cache);
extern unsigned char cache_full(struct cache_buffer_t * cache);
extern unsigned char cache_input(struct cache_buffer_t * cache, cache_typedef data);
extern unsigned char cache_output(struct cache_buffer_t * cache, cache_typedef * data);

#endif

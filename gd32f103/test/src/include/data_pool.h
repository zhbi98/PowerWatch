
#ifndef __DATA_POOL_H__
#define __DATA_POOL_H__

#include <stdio.h>
#include <stdbool.h>

#define MAX_DATA_LEN 32
#define MAX_BUF_LEN  32

typedef float pool_data_t;

struct data_pool_t {
    unsigned char phead;
    unsigned char ptail;
    pool_data_t buf[MAX_BUF_LEN];
};

/**
 * example:
 * struct data_pool_t data_pool;
 */

extern void pool_init(struct data_pool_t * pool);
extern unsigned char pool_empty(struct data_pool_t * pool);
extern unsigned char pool_full(struct data_pool_t * pool);
extern unsigned char input_pool(struct data_pool_t * pool, pool_data_t data);
extern unsigned char output_pool(struct data_pool_t * pool, pool_data_t * data);

#endif

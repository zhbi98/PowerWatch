
#include "data_pool.h"

void pool_init(struct data_pool_t * pool)
{
    memset(pool->buf, 0, sizeof(pool->buf));
    pool->phead = 0;
    pool->ptail = 0;
}

unsigned char pool_empty(struct data_pool_t * pool)
{
    if (pool->phead == pool->ptail)
        return true;
    else
        return false;
}

unsigned char pool_full(struct data_pool_t * pool)
{
    if (((pool->ptail + 1) % MAX_BUF_LEN) == pool->phead)
        return true;
    else
        return false;
}

unsigned char input_pool(struct data_pool_t * pool, pool_data_t data)
{
    if (pool_full(pool))
        return false;

    pool->buf[pool->ptail] = data;
    pool->ptail += 1;

    pool->ptail = pool->ptail % MAX_BUF_LEN;
    return true;
}

unsigned char output_pool(struct data_pool_t * pool, pool_data_t * data)
{
    if (pool_empty(pool))
        return false;

    *data = pool->buf[pool->phead];
    pool->phead += 1;

    pool->phead = pool->phead % MAX_BUF_LEN;
    return true;
}

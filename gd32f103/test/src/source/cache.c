
#include "cache.h"

void cache_init(struct cache_buffer_t * cache)
{
    cache->phead = 0;
    cache->ptail = 0;
    memset(cache->buf, 0, sizeof(cache->buf));
}

unsigned char cache_empty(struct cache_buffer_t * cache)
{
    if (cache->phead == cache->ptail)
        return true;
    return false;
}

unsigned char cache_full(struct cache_buffer_t * cache)
{
    if (((cache->ptail + 1) % MAX_BUF_LEN) == cache->phead)
        return true;
    return false;
}

unsigned char cache_input(struct cache_buffer_t * cache, cache_typedef data)
{
    if (cache_full(cache))
        return false;

    cache->buf[cache->ptail] = data;
    cache->ptail += 1;
    cache->ptail = cache->ptail % MAX_BUF_LEN;

    return true;
}

unsigned char cache_output(struct cache_buffer_t * cache, cache_typedef * data)
{
    if (cache_empty(cache))
        return false;

    *data = cache->buf[cache->phead];
    cache->phead += 1;
    cache->phead = cache->phead % MAX_BUF_LEN;

    return true;
}

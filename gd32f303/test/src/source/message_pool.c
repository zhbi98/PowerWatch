
#include "message_pool.h"

struct message_pool_t message_pool;

void pool_init(struct message_pool_t * pool)
{
    memset(pool->buf, 0, sizeof(pool->buf));
    pool->phead = 0;
    pool->ptail = 0;
}

unsigned char pool_empty(struct message_pool_t * pool)
{
    if (pool->phead == pool->ptail)
        return true;
    else
        return false;
}

unsigned char pool_full(struct message_pool_t * pool)
{
    if (((pool->ptail + 1) % MAX_BUF_LEN) == pool->phead)
        return true;
    else
        return false;
}

unsigned char input_pool(struct message_pool_t * pool, unsigned char * message, unsigned char message_len)
{
    unsigned char len = 0;

    if (pool_full(pool))
        return false;

    while (len < message_len) {
        pool->buf[pool->ptail].message[len] = message[len];
        len++;
    }

    // strcpy for copy exists 0x00 byte data will go wrong,
    // because strcpy unable to copy 0x00
    // strcpy(pool->buf[pool->ptail].message, message);

    // usart_send_string(message);
    // usart_send_string(pool->buf[pool->ptail].message);
    pool->buf[pool->ptail].length = message_len;
    pool->buf[pool->ptail].executed = false;
    pool->ptail += 1;

    pool->ptail = pool->ptail % MAX_BUF_LEN;
    return true;
}

unsigned char output_pool(struct message_pool_t * pool, struct controller_t * controller_message)
{
    unsigned char len = 0;

    if (pool_empty(pool))
        return false;

    *controller_message = pool->buf[pool->phead];
    // usart_send_string(pool->buf[pool->phead].message);
    pool->phead += 1;

    pool->phead = pool->phead % MAX_BUF_LEN;
    return true;
}

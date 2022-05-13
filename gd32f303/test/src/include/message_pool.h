
#ifndef __MESSAGE_POOL_H__
#define __MESSAGE_POOL_H__

#include <stdio.h>
#include <stdbool.h>

#include "usart.h"

#define MAX_DATA_LEN 32
#define MAX_BUF_LEN  32

struct controller_t {
    char message[MAX_DATA_LEN];
    unsigned char length;
    unsigned char executed;
};

struct message_pool_t {
    unsigned char phead;
    unsigned char ptail;
    struct controller_t buf[MAX_BUF_LEN];
};

extern struct message_pool_t message_pool;

extern void pool_init(struct message_pool_t * pool);
extern unsigned char pool_empty(struct message_pool_t * pool);
extern unsigned char pool_full(struct message_pool_t * pool);

extern unsigned char input_pool(struct message_pool_t * pool, unsigned char * message, unsigned char message_len);
extern unsigned char output_pool(struct message_pool_t * pool, struct controller_t * controller_message);

#endif

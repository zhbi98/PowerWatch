/**
 * @file nt_qq.h
 *
 */

#ifndef __NT_QQ_H__
#define __NT_QQ_H__

/*********************
 *      INCLUDES
 *********************/

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

#define NODE_SIZE 1024
#define NODE_NUM  8

/*Dummy type to make handling easier*/
typedef uint8_t nt_qq_node_t;

typedef struct {
    uint32_t n_size;
    uint8_t phead;
    uint8_t ptail;
    nt_qq_node_t nodes[NODE_SIZE];
} nt_qq_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void _nt_qq_init(nt_qq_t * qq_p, uint32_t node_size);
uint8_t _nt_qq_is_empty(nt_qq_t * qq_p);
uint8_t _nt_qq_is_full(nt_qq_t * qq_p);
uint8_t _nt_qq_ins(nt_qq_t * qq_p, void * node_p);
uint8_t _nt_qq_remove(nt_qq_t * qq_p, void * node_p);
uint8_t _nt_qq_clear(nt_qq_t * qq_p);
uint32_t _nt_qq_get_len(nt_qq_t * qq_p);

#endif /*NT_QQ_H*/

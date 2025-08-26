/**
 * @file nt_qq.c
 *
 */

#include "nt_qq.h"


/**
 * Initialize qq
 * @param qq_p pointer to nt_qq_t variable
 * @param node_size the size of 1 node in bytes
 */
void _nt_qq_init(nt_qq_t * qq_p, uint32_t node_size)
{
    qq_p->phead = 0;
    qq_p->ptail = 0;

#ifdef NT_ARCH_64
    /*Round the size up to 8*/
    node_size = (node_size + 7) & (~0x7);
#else
    /*Round the size up to 4*/
    node_size = (node_size + 3) & (~0x3);
#endif
    qq_p->n_size = node_size;
    memset(qq_p->nodes, 0, sizeof(nt_qq_node_t) * NODE_SIZE);
}

/**
 * Check qq if the contents are empty
 * @param qq_p pointer to nt_qq_t variable
 * @param node_size the size of 1 node in bytes
 */
uint8_t _nt_qq_is_empty(nt_qq_t * qq_p)
{
    if (qq_p->phead == qq_p->ptail) return true;
    else return false;
}

/**
 * Check qq if the contents are full
 * @param qq_p pointer to nt_qq_t variable
 * @param node_size the size of 1 node in bytes
 */
uint8_t _nt_qq_is_full(nt_qq_t * qq_p)
{
    if (((qq_p->ptail + 1) % NODE_NUM) == qq_p->phead)
        return true;
    else return false;
}

/**
 * Add a new head to a qq
 * @param qq_p pointer to qq
 * @return pointer to the new head
 */
uint8_t _nt_qq_ins(nt_qq_t * qq_p, void * node_p)
{
    if (_nt_qq_is_full(qq_p)) return false;

    memcpy(&qq_p->nodes[qq_p->ptail * qq_p->n_size], node_p, qq_p->n_size);

    qq_p->ptail += 1;
    qq_p->ptail = qq_p->ptail % NODE_NUM;
    return true;
}

/**
 * Remove the node 'node_p' from 'qq_p' qq list.
 * It does not free the memory of node.
 * @param qq_p pointer to the qq of 'node_p'
 * @param node_p pointer to node in 'qq_p' qq
 */
uint8_t _nt_qq_remove(nt_qq_t * qq_p, void * node_p)
{
    if (_nt_qq_is_empty(qq_p)) return false;

    memcpy(node_p, &qq_p->nodes[qq_p->phead * qq_p->n_size], qq_p->n_size);

    qq_p->phead += 1;
    qq_p->phead = qq_p->phead % NODE_NUM;
    return true;
}

/**
 * Remove and free all elements from a qq. The qq remain valid but become empty.
 * @param qq_p pointer to qq
 */
uint8_t _nt_qq_clear(nt_qq_t * qq_p)
{
    if (_nt_qq_is_empty(qq_p)) return true;
    memset(qq_p->nodes, 0, sizeof(nt_qq_node_t) * NODE_SIZE);
    qq_p->phead = 0;
    qq_p->ptail = 0;
    return true;
}

/**
 * Return the length of the qq.
 * @param qq_p pointer to qq
 * @return length of the qq
 */
uint32_t _nt_qq_get_len(nt_qq_t * qq_p)
{
    if (_nt_qq_is_empty(qq_p)) return 0;
    return (qq_p->ptail - qq_p->phead + NODE_SIZE) % NODE_SIZE;
}

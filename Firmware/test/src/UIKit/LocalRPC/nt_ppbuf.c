/**
 * @file nt_ppbuf.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "nt_ppbuf.h"

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * initialization a Ping-pong buffer.
 * @param ppbuf Pointer to the ping-pong buffer structure.
 * @param buf0 Pointer to the first buffer.
 * @param buf1 Pointer to the second buffer.
 */
void nt_ppbuf_init(nt_ppbuf_t * ppbuf, void * buf0, void * buf1)
{
    memset(ppbuf, 0, sizeof(nt_ppbuf_t));
    ppbuf->buffer[0] = buf0;
    ppbuf->buffer[1] = buf1;
}

/**
 * Get a readable buffer.
 * @param ppbuf Pointer to the ping-pong buffer structure.
 * @param prbuf Pointer to the pointer to the buffer to be read.
 * @return true if there is a buffer to be read.
 */
bool nt_ppbuf_get_read_buf(nt_ppbuf_t * ppbuf, void ** prbuf)
{
    if (ppbuf->r_valid[0]) ppbuf->r_idx = 0;
    else if (ppbuf->r_valid[1]) ppbuf->r_idx = 1;
    else return false;

    *prbuf = ppbuf->buffer[ppbuf->r_idx];
    return true;
}

/**
 * Notify buffer read completion.
 * @param ppbuf Pointer to the ping-pong buffer structure.
 */
void nt_ppbuf_read_done(nt_ppbuf_t * ppbuf)
{
    ppbuf->r_valid[ppbuf->r_idx] = false;
}

/**
 * Get writable buffer.
 * @param ppbuf Pointer to the ping-pong buffer structure.
 * @param pwbuf Pointer to the pointer to the buffer to be wriye.
 */
void nt_ppbuf_get_write_buf(nt_ppbuf_t * ppbuf, void ** pwbuf)
{
    if (ppbuf->w_idx == ppbuf->r_idx)
        ppbuf->w_idx = !ppbuf->r_idx;
    *pwbuf = ppbuf->buffer[ppbuf->w_idx];
}

/**
 * Notify buffer write completion.
 * @param ppbuf Pointer to the ping-pong buffer structure.
 */
void nt_ppbuf_write_done(nt_ppbuf_t * ppbuf)
{
    ppbuf->r_valid[ppbuf->w_idx] = true;
    ppbuf->w_idx = !ppbuf->w_idx;
}

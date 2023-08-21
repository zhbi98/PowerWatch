/**
 * @file nt_ppbuf.h
 *
 */

#ifndef __NT_PPBUF_H__
#define __NT_PPBUF_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/*********************
 *      DEFINES
 *********************/

#ifndef __IO
#define __IO volatile
#endif

/**********************
 *      TYPEDEFS
 **********************/

/*Construct a ppbuf manager type*/
typedef struct {
    void * buffer[2];
    __IO uint8_t w_idx;
    __IO uint8_t r_idx;
    __IO uint8_t r_valid[2];
} nt_ppbuf_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void nt_ppbuf_init(nt_ppbuf_t * ppbuf, void * buf0, void * buf1);
bool nt_ppbuf_get_read_buf(nt_ppbuf_t * ppbuf, void ** prbuf);
void nt_ppbuf_read_done(nt_ppbuf_t * ppbuf);
void nt_ppbuf_get_write_buf(nt_ppbuf_t * ppbuf, void ** pwbuf);
void nt_ppbuf_write_done(nt_ppbuf_t * ppbuf);

#endif /*__NT_PPBUF_H__*/

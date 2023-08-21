/**
 * @file nt_master.h
 *
 */

#ifndef __NT_MASTER_H__
#define __NT_MASTER_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>
#include "lvgl.h"
#include "nt_account.h"

/**********************
 *      TYPEDEFS
 **********************/
/**
 * NT master error codes.
 */
enum {
    NT_MASTER_INV = 0, /*Typically indicates that the object is deleted (become invalid) in the action
                      function or an operation was failed*/
    NT_MASTER_OK,      /*The object is valid (no deleted) after the action*/
};

typedef uint8_t nt_master_res_t;

typedef struct {
	lv_ll_t accounts_ll; /**< List Accounts*/
} nt_master_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void _nt_master_init(nt_master_t * master_p);
uint8_t nt_master_add_acct(nt_master_t * master_p, nt_acct_t * acct_p);
uint8_t nt_master_remove_acct(nt_master_t * master_p, nt_acct_t * acct_p);
uint32_t nt_master_get_len(nt_master_t * master_p);

#endif /*__NT_MASTER_H__*/

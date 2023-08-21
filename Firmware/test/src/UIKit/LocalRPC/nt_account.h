/**
 * @file nt_account.h
 *
 */

#ifndef __NT_ACCOUNT_H__
#define __NT_ACCOUNT_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>
#include <stdbool.h>
#include "nt_ppbuf.h"
#include "lvgl.h"
#include "log.h"

/*********************
 *      DEFINES
 *********************/

/*
 * Set up an account for the data member and specify the account name. This builds a 
 * struct of type nt_acct_t.
 */
#define NT_ACCTOUNT_START(_name, _namestr) \
    nt_acct_t _acct##_name \
    .acct_id = _namestr, \
    .publishers_ll = {0}, \
    .subscribers_ll = {0}, \
    .priv = {0}

#define NT_ACCTOUNT_END \
};

/**********************
 *      TYPEDEFS
 **********************/

/**
 * NT account error code.
 */
enum {
    NT_ACCT_RES_OK =  0,
    NT_ACCT_RES_UNKNOW = -1,
    NT_ACCT_RES_SIZE_MISMATCH = -2,
    NT_ACCT_RES_UNSUPPORTED_REQUEST = -3,
    NT_ACCT_RES_NO_CALLBACK = -4,
    NT_ACCT_RES_NO_CACHE = -5,
    NT_ACCT_RES_NO_COMMITED = -6,
    NT_ACCT_RES_NOT_FOUND = -7,
    NT_ACCT_RES_PARAM_ERROR = -8
};

typedef int8_t nt_acct_res_t;

/**
 * NT account event type.
 */
enum {
    NT_ACCT_EVENT_NONE = 0,
    NT_ACCT_EVENT_PUB_PUBLISH, /**< Publisher posted information*/
    NT_ACCT_EVENT_SUB_PULL,    /**< Subscriber data pull request*/
    NT_ACCT_EVENT_NOTIFY,      /**< Subscribers send notifications to publishers*/
    NT_ACCT_EVENT_TIMER,       /**< Timed event*/
    _NT_ACCT_EVENT_LAST
};

typedef uint8_t nt_acct_event_t;

/**
 * NT account state codes.
 */
enum {
    NT_ACCT_INV = 0, /*Typically indicates that the object is deleted (become invalid) in the action
                      function or an operation was failed*/
    NT_ACCT_OK,      /*The object is valid (no deleted) after the action*/
};

typedef int8_t nt_acct_state_t;

/**
 * Construct event parameter structure.
 */
typedef struct {
    nt_acct_event_t event;    /**< Event type*/
    struct _nt_acct_t * tran; /**< Pointer to sender*/
    struct _nt_acct_t * recv; /**< Pointer to receiver*/
    void * data_p;            /**< Pointer to data*/
    uint32_t size;            /**< The length of the data*/
} _nt_acct_event_param_t;

/**
 * Construct a account type.
 */
typedef struct _nt_acct_t {
    const int8_t * acct_id; /**< Unique account id*/
    void * userdata;        /**< Used to pass some user-defined data*/
    lv_ll_t publishers_ll;  /**< Followed publishers*/
    lv_ll_t subscribers_ll; /**< Followed subscribers*/

    struct _nt_priv_t {
        int32_t (* event_callback)(struct _nt_acct_t * acct, 
            _nt_acct_event_param_t * param);
        lv_timer_t * timer;
        nt_ppbuf_t ppbuf;
        uint8_t * buf0;
        uint8_t * buf1;
        uint32_t buffersize;
    } priv;
} nt_acct_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

uint8_t nt_acct_constructor(nt_acct_t * acct_p, const int8_t * acct_id, 
    uint32_t bufsize, void * userdata);
void nt_acct_destructor(nt_acct_t * acct_p);
nt_acct_t * nt_acct_subscribe(nt_acct_t * acct_p, const int8_t * pub_id);
uint8_t nt_acct_unsubscribe(nt_acct_t * acct_p, const int8_t * pub_id);
uint8_t nt_acct_commit(nt_acct_t * acct_p, const void * data_p, uint32_t size);
int32_t nt_acct_publish(nt_acct_t * acct_p);
int32_t nt_acct_notify(nt_acct_t * acct_p, const int8_t * pub_id, 
    const void * data_p, uint32_t size);
void nt_acct_set_event_callback(nt_acct_t * acct_p, int (* callback)(
    struct _nt_acct_t * acct, _nt_acct_event_param_t * param));
uint32_t nt_acct_get_publishers_size(nt_acct_t * acct_p);
uint32_t nt_acct_get_subscribers_size(nt_acct_t * acct_p);

#endif /*__NT_ACCOUNT_H__*/

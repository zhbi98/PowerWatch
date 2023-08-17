/**
 * @file sheet.h
 *
 */

#ifndef __RECENT_H__
#define __RECENT_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdlib.h>
#include "cache.h"
#include "strifica.h"
#include "recentview.h"
#include "nt_pm.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern const nt_view_t recentview;
extern struct cache_buffer_t bar_cache_buf;
extern void bar_cache_hanlder(float value);

#endif /*__SHEET_H__*/

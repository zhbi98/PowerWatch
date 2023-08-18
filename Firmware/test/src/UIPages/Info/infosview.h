/**
 * @file recentview.h
 *
 */

#ifndef __INFOS_VIEW_H__
#define __INFOS_VIEW_H__

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"
#include "usr_symbol_def.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    lv_obj_t * cont;
    lv_style_t style;
    lv_style_t _style;
} nt_infos_view_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern nt_infos_view_t infos_view;

/**********************
 * GLOBAL FUNCTIONS
 **********************/

void infos_create(lv_obj_t * par);

#endif /*__INFOS_VIEW_H__*/

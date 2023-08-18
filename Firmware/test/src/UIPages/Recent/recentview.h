/**
 * @file recentview.h
 *
 */

#ifndef __RECENT_VIEW_H__
#define __RECENT_VIEW_H__

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"

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

    struct {
        lv_obj_t * chart;
        lv_chart_series_t * ser;
        lv_obj_t * unit_label;
    } chart;
} nt_recent_view_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern nt_recent_view_t recent_view;

/**********************
 * GLOBAL FUNCTIONS
 **********************/

void nt_recent_create(lv_obj_t * par);

#endif /*__RECENT_VIEW_H__*/

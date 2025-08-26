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
        lv_obj_t * cont;

        struct {
            lv_obj_t * cont;
            lv_obj_t * label;
        } title;

        struct {
            lv_obj_t * cont;
            lv_obj_t * label;
        } time;

        struct {
            lv_obj_t * cont;
            lv_obj_t * bar;
        } bar;
    } estimate;

    struct {
        lv_obj_t * cont;

        struct {
            lv_obj_t * cont;
            lv_obj_t * label;
        } title;

        struct {
            lv_obj_t * spin;
            lv_obj_t * incr_btn;
            lv_obj_t * decr_btn;
        } spinbox;
    } capacity;

    struct {
        lv_obj_t * cont;
        lv_obj_t * title_label;

        struct {
            lv_obj_t * spin;
            lv_obj_t * incr_btn;
            lv_obj_t * decr_btn;
        } spinbox;
    } quantity;

    lv_obj_t * start_btn;
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

/**
 * @file dialplateview.h
 *
 */

#ifndef __DIALPLATEVIEW_H__
#define __DIALPLATEVIEW_H__

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

    lv_style_t style_iden;
    lv_style_t style_iden_cont;

    struct {
        lv_obj_t * cont;
        lv_style_t style;

        struct {
            lv_obj_t * cont;
            lv_obj_t * value_label;
            lv_obj_t * unit_label;
        } main_0;

        struct {
            lv_obj_t * cont;
            lv_obj_t * value_label;
            lv_obj_t * unit_label;
        } main_1;
    } main;

    struct {
        lv_obj_t * cont;
        lv_style_t style;

        struct {
            lv_obj_t * cont;
            lv_obj_t * label;
        } title;

        struct {
            lv_obj_t * cont;
            lv_obj_t * label;
            lv_obj_t * sym_label;
        } dura;
    } duration;

    struct {
        lv_obj_t * cont;
        lv_style_t style;
        lv_style_t style_points;

        struct {
            lv_obj_t * cont;
            lv_obj_t * title_label;
            lv_obj_t * value_label;
        } node_0;

        struct {
            lv_obj_t * cont;
            lv_obj_t * title_label;
            lv_obj_t * value_label;
        } node_1;

        struct {
            lv_obj_t * cont;
            lv_obj_t * title_label;
            lv_obj_t * value_label;
        } node_2;

        struct {
            lv_obj_t * cont;
            lv_obj_t * title_label;
            lv_obj_t * value_label;
        } node_3;
    } count;
} nt_dialplate_view_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern nt_dialplate_view_t dialview;

/**********************
 * GLOBAL FUNCTIONS
 **********************/

void nt_dialplate_create(lv_obj_t * par);

#endif /*__DIALPLATEVIEW_H__*/

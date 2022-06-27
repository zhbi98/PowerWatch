
#ifndef __MEAS_VIEW_H__
#define __MEAS_VIEW_H__

#include "lvgl.h"
#include "usr_symbol_def.h"

typedef struct {
    lv_obj_t * cont1;
    lv_obj_t * labelValue1;
    lv_obj_t * labelUnit1;
    lv_obj_t * cont2;
    lv_obj_t * labelValue2;
    lv_obj_t * labelUnit2;
    lv_obj_t * cont3;
    lv_obj_t * labelValue3;
    lv_style_t style;
} MainShow;

typedef struct {
    lv_obj_t * cont;
    lv_obj_t * labelValue1;
    lv_obj_t * labelValue2;
    lv_obj_t * labelValue3;
    lv_obj_t * labelValue4;
    lv_obj_t * labelUnit1;
    lv_obj_t * labelUnit2;
    lv_obj_t * labelUnit3;
    lv_obj_t * labelUnit4;
    lv_style_t labelStyle;
} Sidebar;

typedef struct {
    lv_obj_t * cont;
    lv_style_t style;

    MainShow mainShow;
    Sidebar sidebar;
} MeasSence;

extern MeasSence measSence;

extern void measViewCreate(lv_obj_t * root);
extern void mainShowViewCreate(lv_obj_t * par);
extern void sidebarViewCreate(lv_obj_t * par);

#endif

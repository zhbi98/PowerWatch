
#ifndef __ABOUT_VIEW_H__
#define __ABOUT_VIEW_H__

#include "lvgl.h"

typedef struct {
    lv_obj_t * label;
    lv_style_t style;
} Title;

typedef struct {
    lv_obj_t * cont;
    lv_style_t style;
    Title title;
    lv_obj_t * button;
} AboutSence;

extern AboutSence aboutSence;

extern void aboutViewCreate(lv_obj_t * root);

#endif

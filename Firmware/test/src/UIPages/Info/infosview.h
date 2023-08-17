
#ifndef __INFOS_VIEW_H__
#define __INFOS_VIEW_H__

#include "lvgl.h"
#include "usr_symbol_def.h"

typedef struct {
    lv_obj_t * cont;
    lv_obj_t * labelTitle;
    lv_obj_t * labelVersion;
    lv_obj_t * labelDesign;
    lv_style_t style;
} Title;

typedef struct {
    lv_obj_t * cont;
    lv_obj_t * labelLogo;
    lv_obj_t * labelTemp;
    lv_obj_t * labelUnit;
    lv_style_t style;
} Temp;

typedef struct {
    lv_obj_t * cont;
    lv_obj_t * labelLvgl;
    lv_obj_t * labelMcu;
    lv_obj_t * labelFlash;
    lv_style_t style;
} DeviceInfo;

typedef struct {
    lv_obj_t * cont;
    lv_style_t style;
    Title title;
    Temp temp;
    DeviceInfo deviceInfo;
} AboutSence;

extern AboutSence aboutSence;

extern void aboutViewCreate(lv_obj_t * root);
extern void titleViewCreate(lv_obj_t * par);
extern void tempViewCreate(lv_obj_t * par);
extern void infoViewCreate(lv_obj_t * par);

#endif

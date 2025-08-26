/**
 * @file nt_anim.h
 *
 */

#ifndef __NT_ANIM_H__
#define __NT_ANIM_H__

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"

/*********************
 *      DEFINES
 *********************/

#define NT_HOR_RES 320U
#define NT_VER_RES 170U

/**********************
 *      TYPEDEFS
 **********************/

/*Page switching animation type*/
typedef enum {
    /*Default (global) animation type*/
    LOAD_ANIM_GLOBAL = 0,

    /* New page overwrites old page*/
    LOAD_ANIM_OVER_LEFT,
    LOAD_ANIM_OVER_RIGHT,
    LOAD_ANIM_OVER_TOP,
    LOAD_ANIM_OVER_BOTTOM,

    /*New page pushes old page*/
    LOAD_ANIM_MOVE_LEFT,
    LOAD_ANIM_MOVE_RIGHT,
    LOAD_ANIM_MOVE_TOP,
    LOAD_ANIM_MOVE_BOTTOM,

    /*The new interface fades in, the old page fades out*/
    LOAD_ANIM_FADE_ON,

    /*No animation */
    LOAD_ANIM_NONE,

    _LOAD_ANIM_LAST = LOAD_ANIM_NONE
} nt_load_anim_t;

/*Page switching animation properties*/
typedef struct {
    uint8_t type;
    uint16_t time;
    lv_anim_path_cb_t path;
} anim_attr_t;

/*Animated setter*/
typedef void(*lv_anim_setter_t)(void*, int32_t);

/*Animated getter*/
typedef int32_t(*lv_anim_getter_t)(void*);

/*Animation switching record*/
typedef struct {
    /*As the entered party*/
    struct {
        int32_t start;
        int32_t end;
    } enter;

    /*As the exited party*/
    struct {
        int32_t start;
        int32_t end;
    } exit;
} anim_value_t;

/*Page loading animation properties*/
typedef struct {
    lv_anim_setter_t setter;
    lv_anim_getter_t getter;
    anim_value_t push;
    anim_value_t pop;
} load_anim_attr_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

bool nt_anim_loadanim_get_attr(uint8_t anim, 
    load_anim_attr_t * attr);

#endif /*__NT_ANIM_H__*/

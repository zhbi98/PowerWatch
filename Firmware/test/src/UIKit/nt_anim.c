/**
 * @file nt_anim.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "nt_anim.h"

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void nt_anim_obj_set_opa(const lv_obj_t * obj, int32_t v);
static int32_t nt_anim_obj_get_opa(const lv_obj_t * obj);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Set animation default parameters.
 * @param a pointer to an 'lv_anim_t' animation.
 */
bool nt_anim_loadanim_get_attr(uint8_t anim, 
    load_anim_attr_t * attr)
{
    lv_coord_t hor = NT_HOR_RES;
    lv_coord_t ver = NT_VER_RES;

    uint8_t load_anim_dir = 0;

    switch (anim) {
    case LOAD_ANIM_OVER_LEFT:
        load_anim_dir = 0;

        attr->push.enter.start = hor;
        attr->push.enter.end = 0;
        attr->push.exit.start = 0;
        attr->push.exit.end = 0;

        attr->pop.enter.start = 0;
        attr->pop.enter.end = 0;
        attr->pop.exit.start = 0;
        attr->pop.exit.end = hor;
        break;

    case LOAD_ANIM_OVER_RIGHT:
        load_anim_dir = 0;

        attr->push.enter.start = -hor;
        attr->push.enter.end = 0;
        attr->push.exit.start = 0;
        attr->push.exit.end = 0;

        attr->pop.enter.start = 0;
        attr->pop.enter.end = 0;
        attr->pop.exit.start = 0;
        attr->pop.exit.end = -hor;
        break;

    case LOAD_ANIM_OVER_TOP:
        load_anim_dir = 1;

        attr->push.enter.start = ver;
        attr->push.enter.end = 0;
        attr->push.exit.start = 0;
        attr->push.exit.end = 0;

        attr->pop.enter.start = 0;
        attr->pop.enter.end = 0;
        attr->pop.exit.start = 0;
        attr->pop.exit.end = ver;
        break;

    case LOAD_ANIM_OVER_BOTTOM:
        load_anim_dir = 1;

        attr->push.enter.start = -ver;
        attr->push.enter.end = 0;
        attr->push.exit.start = 0;
        attr->push.exit.end = 0;

        attr->pop.enter.start = 0;
        attr->pop.enter.end = 0;
        attr->pop.exit.start = 0;
        attr->pop.exit.end = -ver;
        break;

    case LOAD_ANIM_MOVE_LEFT:
        load_anim_dir = 0;

        attr->push.enter.start = hor;
        attr->push.enter.end = 0;
        attr->push.exit.start = 0;
        attr->push.exit.end = -hor;

        attr->pop.enter.start = -hor;
        attr->pop.enter.end = 0;
        attr->pop.exit.start = 0;
        attr->pop.exit.end = hor;
        break;

    case LOAD_ANIM_MOVE_RIGHT:
        load_anim_dir = 0;

        attr->push.enter.start = -hor;
        attr->push.enter.end = 0;
        attr->push.exit.start = 0;
        attr->push.exit.end = hor;

        attr->pop.enter.start = hor;
        attr->pop.enter.end = 0;
        attr->pop.exit.start = 0;
        attr->pop.exit.end = -hor;
        break;

    case LOAD_ANIM_MOVE_TOP:
        load_anim_dir = 1;

        attr->push.enter.start = ver;
        attr->push.enter.end = 0;
        attr->push.exit.start = 0;
        attr->push.exit.end = -ver;

        attr->pop.enter.start = -ver;
        attr->pop.enter.end = 0;
        attr->pop.exit.start = 0;
        attr->pop.exit.end = ver;
        break;

    case LOAD_ANIM_MOVE_BOTTOM:
        load_anim_dir = 1;

        attr->push.enter.start = -ver;
        attr->push.enter.end = 0;
        attr->push.exit.start = 0;
        attr->push.exit.end = ver;

        attr->pop.enter.start = ver;
        attr->pop.enter.end = 0;
        attr->pop.exit.start = 0;
        attr->pop.exit.end = -ver;
        break;

    case LOAD_ANIM_FADE_ON:
        load_anim_dir = 2;

        attr->push.enter.start = LV_OPA_TRANSP;
        attr->push.enter.end = LV_OPA_COVER;
        attr->push.exit.start = LV_OPA_COVER;
        attr->push.exit.end = LV_OPA_COVER;

        attr->pop.enter.start = LV_OPA_COVER;
        attr->pop.enter.end = LV_OPA_COVER;
        attr->pop.exit.start = LV_OPA_COVER;
        attr->pop.exit.end = LV_OPA_TRANSP;
        break;

    case LOAD_ANIM_NONE:
        memset(attr, 0, sizeof(load_anim_attr_t));
        return true;

    default: return false;
    }

    if (load_anim_dir == 0) {
        attr->setter = lv_obj_set_x;
        attr->getter = lv_obj_get_x;
    }
    else
    if (load_anim_dir == 1) {
        attr->setter = lv_obj_set_y;
        attr->getter = lv_obj_get_y;
    }
    else {
        attr->setter = nt_anim_obj_set_opa;
        attr->getter = nt_anim_obj_get_opa;
    }

    return true;
}

/**
 * Set animation default parameters.
 * @param a pointer to an 'lv_anim_t' animation.
 */
void nt_anim_obj_set_opa(const lv_obj_t * obj, int32_t v)
{
    lv_obj_set_style_bg_opa((lv_obj_t *)obj, 
        (lv_opa_t)v, LV_PART_MAIN);
}

/**
 * Set animation default parameters.
 * @param a pointer to an 'lv_anim_t' animation.
 */
int32_t nt_anim_obj_get_opa(const lv_obj_t * obj)
{
    lv_opa_t opa = lv_obj_get_style_bg_opa(
        (lv_obj_t *)obj, LV_PART_MAIN);

    return (int32_t)opa;
}

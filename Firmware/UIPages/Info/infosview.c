/**
 * @file infosview.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "infosview.h"
#include "resource.h"

/*********************
 *      DEFINES
 *********************/

#define INFOS_HOR 170
#define INFOS_VER 320

/**********************
 *      TYPEDEFS
 **********************/

nt_infos_view_t infos_view;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void nt_infos_style_create();

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*LV_FONT_DECLARE(font_bahnschrift_17);*/
/*LV_FONT_DECLARE(font_bahnschrift_32);*/
/*LV_FONT_DECLARE(font_bahnschrift_56);*/

void nt_infos_style_create()
{
    /*Reset style*/
    lv_style_reset(&infos_view.style);
    lv_style_init(&infos_view.style);
    lv_style_set_radius(&infos_view.style, 0);
    lv_style_set_bg_color(&infos_view.style, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_opa(&infos_view.style, LV_OPA_100);
    lv_style_set_border_width(&infos_view.style, 0);
    lv_style_set_border_color(&infos_view.style, lv_color_hex(0x000000));
    lv_style_set_border_opa(&infos_view.style, LV_OPA_100);
    lv_style_set_text_color(&infos_view.style, lv_color_hex(0x000000));

    /*Reset style*/
    lv_style_reset(&infos_view._style);
    lv_style_init(&infos_view._style);
    lv_style_set_radius(&infos_view._style, 0);
    lv_style_set_bg_color(&infos_view._style, lv_color_hex(0xFF5136));
    lv_style_set_bg_opa(&infos_view._style, LV_OPA_100);
    lv_style_set_border_width(&infos_view._style, 0);
    lv_style_set_border_color(&infos_view._style, lv_color_hex(0x000000));
    lv_style_set_border_opa(&infos_view._style, LV_OPA_100);
    lv_style_set_text_color(&infos_view._style, lv_color_hex(0x000000));
}

void infos_create(lv_obj_t * par)
{
    lv_obj_remove_style_all(par);
    lv_obj_set_size(par, INFOS_VER, INFOS_HOR);

    nt_infos_style_create();

#define CTEST 0U
#if CTEST
    lv_obj_add_style(par, &infos_view._style, 0);
#else
    lv_obj_add_style(par, &infos_view.style, 0);
#endif

    infos_view.cont = par;
}

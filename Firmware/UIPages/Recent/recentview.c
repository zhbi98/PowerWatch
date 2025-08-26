/**
 * @file recentview.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "recentview.h"
#include "resource.h"

/*********************
 *      DEFINES
 *********************/

#define RECENT_HOR 170
#define RECENT_VER 320

/**********************
 *      TYPEDEFS
 **********************/

nt_recent_view_t recent_view;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void nt_recent_style_create();
static void draw_event_cb(lv_event_t * e);
static void estimate_create(lv_obj_t * par);
static void capacity_create(lv_obj_t * par);
static void quantity_create(lv_obj_t * par);
/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*LV_FONT_DECLARE(font_bahnschrift_17);*/
/*LV_FONT_DECLARE(font_bahnschrift_32);*/
/*LV_FONT_DECLARE(font_bahnschrift_56);*/

void nt_recent_style_create()
{
    /*Reset style*/
    lv_style_reset(&recent_view.style);
    lv_style_init(&recent_view.style);
    lv_style_set_radius(&recent_view.style, 0);
    lv_style_set_bg_color(&recent_view.style, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_opa(&recent_view.style, LV_OPA_100);
    lv_style_set_border_width(&recent_view.style, 0);
    lv_style_set_border_color(&recent_view.style, lv_color_hex(0x000000));
    lv_style_set_border_opa(&recent_view.style, LV_OPA_100);
    lv_style_set_text_color(&recent_view.style, lv_color_hex(0x000000));

    lv_style_reset(&recent_view._style);
    lv_style_init(&recent_view._style);
    lv_style_set_radius(&recent_view._style, 0);
    lv_style_set_bg_color(&recent_view._style, lv_color_hex(0xFF5136));
    lv_style_set_bg_opa(&recent_view._style, LV_OPA_100);
    lv_style_set_border_width(&recent_view._style, 0);
    lv_style_set_border_color(&recent_view._style, lv_color_hex(0x000000));
    lv_style_set_border_opa(&recent_view._style, LV_OPA_100);
    lv_style_set_text_color(&recent_view._style, lv_color_hex(0x000000));
}

void nt_recent_create(lv_obj_t * par)
{
    /* Note the following */
    lv_obj_remove_style_all(par);
    lv_obj_set_size(par, RECENT_VER, RECENT_HOR);

    nt_recent_style_create();

#define CTEST 0U
#if CTEST
    lv_obj_add_style(par, &recent_view._style, 0);
#else
    lv_obj_add_style(par, &recent_view.style, 0);
#endif

    recent_view.cont = par;

    estimate_create(par);
    capacity_create(par);
    quantity_create(par);
}

void estimate_create(lv_obj_t * par)
{
    lv_obj_t * _label = NULL;
    lv_obj_t * _cont = NULL;
    lv_obj_t * cont = NULL;
    lv_obj_t * bar = NULL;

    lv_font_t * en_17_p = reqfont("bahnschrift_17");
    lv_font_t * en_32_p = reqfont("bahnschrift_32");

    cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_add_style(cont, &recent_view.style, 0);

    lv_obj_set_style_radius(cont, 10, 0);
    lv_obj_set_style_bg_color(cont,  lv_color_hex(0xE0E0E0), 0);
    lv_obj_set_style_bg_opa(cont,  LV_OPA_100, 0);

    lv_obj_set_size(cont, 180, 70);
    lv_obj_set_pos(cont, 10, 10);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);

    static lv_style_t flex_style;
    lv_style_init(&flex_style);
    lv_style_set_flex_flow(&flex_style, LV_FLEX_FLOW_ROW);
    lv_style_set_flex_main_place(&flex_style, LV_FLEX_ALIGN_START);
    lv_style_set_layout(&flex_style, LV_LAYOUT_FLEX);
    lv_style_set_pad_column(&flex_style, 2);
    lv_style_set_pad_row(&flex_style, 4);
    lv_obj_add_style(cont, &flex_style, 0);

    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 110, 34);

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);
    lv_obj_set_style_text_font(_label, en_32_p, 0);
    lv_label_set_text(_label, "20:00");

    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 60, 34);

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);
    lv_obj_set_style_text_font(_label, en_17_p, 0);
    lv_label_set_text(_label, "complet");

    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 180, 35);

    bar = lv_bar_create(_cont);
    lv_obj_align(bar, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(bar, 160, 20);
    lv_bar_set_value(bar, 50, LV_ANIM_ON);
}

void capacity_create(lv_obj_t * par)
{
    lv_obj_t * _label = NULL;
    lv_obj_t * _cont = NULL;
    lv_obj_t * cont = NULL;
    lv_obj_t * spin = NULL;
    lv_obj_t * btn = NULL;

    lv_font_t * en_17_p = reqfont("bahnschrift_17");

    cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_add_style(cont, &recent_view.style, 0);

    lv_obj_set_style_radius(cont, 10, 0);
    lv_obj_set_style_bg_color(cont,  lv_color_hex(0xE0E0E0), 0);
    lv_obj_set_style_bg_opa(cont,  LV_OPA_100, 0);

    lv_obj_set_size(cont, 80, 70);
    lv_obj_set_pos(cont, 10, 90);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);

    static lv_style_t flex_style;
    lv_style_init(&flex_style);
    lv_style_set_flex_flow(&flex_style, LV_FLEX_FLOW_ROW);
    lv_style_set_flex_main_place(&flex_style, LV_FLEX_ALIGN_START);
    lv_style_set_layout(&flex_style, LV_LAYOUT_FLEX);
    lv_style_set_pad_column(&flex_style, 2);
    lv_style_set_pad_row(&flex_style, 4);
    lv_obj_add_style(cont, &flex_style, 0);

    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 80, 34);

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);
    lv_obj_set_style_text_font(_label, en_17_p, 0);
    lv_label_set_text(_label, "capacity");

    btn = lv_btn_create(cont);
    lv_obj_set_size(btn, 15, 30);

    spin = lv_spinbox_create(cont);
    lv_obj_set_size(spin, 40, 30);
    lv_spinbox_set_range(spin, 0, 50000);
    lv_spinbox_set_digit_format(spin, 5, 0);

    btn = lv_btn_create(cont);
    lv_obj_set_size(btn, 15, 30);
}

void quantity_create(lv_obj_t * par)
{
    lv_obj_t * _label = NULL;
    lv_obj_t * _cont = NULL;
    lv_obj_t * cont = NULL;
    lv_obj_t * spin = NULL;
    lv_obj_t * btn = NULL;

    lv_font_t * en_17_p = reqfont("bahnschrift_17");

    cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_add_style(cont, &recent_view.style, 0);

    lv_obj_set_style_radius(cont, 10, 0);
    lv_obj_set_style_bg_color(cont,  lv_color_hex(0xE0E0E0), 0);
    lv_obj_set_style_bg_opa(cont,  LV_OPA_100, 0);

    lv_obj_set_size(cont, 80, 70);
    lv_obj_set_pos(cont, 100, 90);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);

    static lv_style_t flex_style;
    lv_style_init(&flex_style);
    lv_style_set_flex_flow(&flex_style, LV_FLEX_FLOW_ROW);
    lv_style_set_flex_main_place(&flex_style, LV_FLEX_ALIGN_START);
    lv_style_set_layout(&flex_style, LV_LAYOUT_FLEX);
    lv_style_set_pad_column(&flex_style, 2);
    lv_style_set_pad_row(&flex_style, 4);
    lv_obj_add_style(cont, &flex_style, 0);

    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 80, 34);

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);
    lv_obj_set_style_text_font(_label, en_17_p, 0);
    lv_label_set_text(_label, "capacity");

    btn = lv_btn_create(cont);
    lv_obj_set_size(btn, 15, 30);

    spin = lv_spinbox_create(cont);
    lv_obj_set_size(spin, 40, 30);
    lv_spinbox_set_range(spin, 0, 50000);
    lv_spinbox_set_digit_format(spin, 5, 0);

    btn = lv_btn_create(cont);
    lv_obj_set_size(btn, 15, 30);
}

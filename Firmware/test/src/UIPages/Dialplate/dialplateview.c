/**
 * @file dialplateview.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "dialplateview.h"

/*********************
 *      DEFINES
 *********************/

#define DIAL_HOR 170
#define DIAL_VER 320

/**********************
 *      TYPEDEFS
 **********************/

nt_dialplate_view_t dialview;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void nt_dialplate_style_create();
static void nt_dialplate_iden_style_create();
static void nt_dialplate_main_style_create();
static void nt_dialplate_count_style_create();
static void main_create(lv_obj_t * par);
static void duration_create(lv_obj_t * par);
static void count_create(lv_obj_t * par);
/**********************
 * GLOBAL PROTOTYPES
 **********************/

void nt_dialplate_style_create()
{
    /*Reset style*/
    lv_style_reset(&dialview.style);
    lv_style_init(&dialview.style);
    lv_style_set_radius(&dialview.style, 0);
    lv_style_set_bg_color(&dialview.style, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_opa(&dialview.style, LV_OPA_100);
    lv_style_set_border_width(&dialview.style, 0);
    lv_style_set_border_color(&dialview.style, lv_color_hex(0x000000));
    lv_style_set_border_opa(&dialview.style, LV_OPA_100);
    lv_style_set_text_color(&dialview.style, lv_color_hex(0x000000));
    /*lv_obj_add_style(obj, &dialview.style, 0);*/

    /*Reset style*/
    lv_style_reset(&dialview._style);
    lv_style_init(&dialview._style);
    lv_style_set_radius(&dialview._style, 0);
    lv_style_set_bg_color(&dialview._style, lv_color_hex(0xFF5136));
    lv_style_set_bg_opa(&dialview._style, LV_OPA_100);
    lv_style_set_border_width(&dialview._style, 0);
    lv_style_set_border_color(&dialview._style, lv_color_hex(0x000000));
    lv_style_set_border_opa(&dialview._style, LV_OPA_100);
    lv_style_set_text_color(&dialview._style, lv_color_hex(0x000000));
    /*lv_obj_add_style(obj, &dialview._style, 0);*/
}

void nt_dialplate_create(lv_obj_t * par)
{
    /* Note the following */
    lv_obj_remove_style_all(par);
    lv_obj_set_size(par, DIAL_VER, DIAL_HOR);

    nt_dialplate_style_create();

#define DTEST 0U
#if DTEST
    lv_obj_add_style(par, &dialview._style, 0);
#else
    lv_obj_add_style(par, &dialview.style, 0);
#endif

    dialview.cont = par;

    nt_dialplate_iden_style_create();
    nt_dialplate_main_style_create();
    nt_dialplate_count_style_create();
    main_create(par);
    duration_create(par);
    count_create(par);
}

void nt_dialplate_iden_style_create()
{
    /*Reset style*/
    lv_style_reset(&dialview.style_iden);
    lv_style_init(&dialview.style_iden);
    lv_style_set_radius(&dialview.style_iden, 0);
    lv_style_set_bg_color(&dialview.style_iden, lv_color_hex(0x000000));
    lv_style_set_bg_opa(&dialview.style_iden, LV_OPA_0);
    lv_style_set_border_width(&dialview.style_iden, 0);
    lv_style_set_border_color(&dialview.style_iden, lv_color_hex(0x000000));
    lv_style_set_border_opa(&dialview.style_iden, LV_OPA_0);
    lv_style_set_text_color(&dialview.style_iden, lv_color_hex(0x000000));
    /*lv_obj_add_style(obj, &dialview.style_iden, 0);*/

    /*Reset style*/
    lv_style_reset(&dialview.style_iden_cont);
    lv_style_init(&dialview.style_iden_cont);
    lv_style_set_radius(&dialview.style_iden_cont, 0);
    lv_style_set_bg_color(&dialview.style_iden_cont, lv_color_hex(0x000000));
    lv_style_set_bg_opa(&dialview.style_iden_cont, LV_OPA_0);
    lv_style_set_border_width(&dialview.style_iden_cont, 0);
    lv_style_set_border_color(&dialview.style_iden_cont, lv_color_hex(0x000000));
    lv_style_set_border_opa(&dialview.style_iden_cont, LV_OPA_0);
    lv_style_set_text_color(&dialview.style_iden_cont, lv_color_hex(0x000000));
    /*lv_obj_add_style(obj, &dialview.style_iden_cont, 0);*/
}

void nt_dialplate_main_style_create()
{
    /*Reset style*/
    lv_style_reset(&dialview.main.style);
    lv_style_init(&dialview.main.style);
    lv_style_set_radius(&dialview.main.style, 0);
    lv_style_set_bg_color(&dialview.main.style, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_opa(&dialview.main.style, LV_OPA_0);
    lv_style_set_border_width(&dialview.main.style, 0);
    lv_style_set_border_color(&dialview.main.style, lv_color_hex(0x000000));
    lv_style_set_border_opa(&dialview.main.style, LV_OPA_100);
    lv_style_set_text_color(&dialview.main.style, lv_color_hex(0x000000));
    /*lv_obj_add_style(obj, &dialview.main.style, 0);*/
}

void main_create(lv_obj_t * par)
{
    lv_obj_t * cont = NULL;
    lv_obj_t * _label = NULL;
    lv_obj_t * _cont = NULL;
    lv_obj_t * _points = NULL;

    cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_add_style(cont, &dialview.main.style, 0);
    lv_obj_set_size(cont, 170, 120);
    lv_obj_set_pos(cont, 10, 10);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);

    static lv_style_t flex_style;
    lv_style_init(&flex_style);
    lv_style_set_flex_flow(&flex_style, LV_FLEX_FLOW_ROW_WRAP);
    lv_style_set_flex_main_place(&flex_style, LV_FLEX_ALIGN_START);
    lv_style_set_layout(&flex_style, LV_LAYOUT_FLEX);
    lv_style_set_pad_column(&flex_style, 0);
    lv_style_set_pad_row(&flex_style, 10);
    lv_obj_add_style(cont, &flex_style, 0);
    dialview.main.cont = cont;

    /*main_0*/
    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 170, 55);
    lv_obj_add_style(_cont, &dialview.main.style, 0);
    lv_obj_set_style_radius(_cont, 18, 0);
    lv_obj_set_style_bg_color(_cont,  lv_color_hex(0xE0E0E0), 0);
    lv_obj_set_style_bg_opa(_cont,  LV_OPA_100, 0);

    lv_obj_set_style_bg_color(_cont, lv_palette_main(LV_PALETTE_ORANGE), LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(_cont, lv_color_hex(0xFFFFFF), LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(_cont, lv_palette_main(LV_PALETTE_DEEP_ORANGE), LV_STATE_PRESSED);

    dialview.main.main_0.cont = _cont;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_CENTER, -29, 0);
    LV_FONT_DECLARE(font_bahnschrift_56);
    /*lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);*/
    lv_obj_set_style_text_font(_label, &font_bahnschrift_56, 0);
    lv_label_set_text(_label, "00.00");
    dialview.main.main_0.value_label = _label;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_CENTER, 52, 5);
    LV_FONT_DECLARE(font_bahnschrift_32);
    /*lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);*/
    lv_obj_set_style_text_font(_label, &font_bahnschrift_32, 0);
    lv_label_set_text(_label, "mWh");
    dialview.main.main_0.unit_label = _label;

    /*main_1*/
    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 170, 55);
    lv_obj_add_style(_cont, &dialview.main.style, 0);
    lv_obj_set_style_radius(_cont, 18, 0);
    lv_obj_set_style_bg_color(_cont,  lv_color_hex(0xE0E0E0), 0);
    lv_obj_set_style_bg_opa(_cont,  LV_OPA_100, 0);

    lv_obj_set_style_bg_color(_cont, lv_palette_main(LV_PALETTE_ORANGE), LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(_cont, lv_color_hex(0xFFFFFF), LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(_cont, lv_palette_main(LV_PALETTE_DEEP_ORANGE), LV_STATE_PRESSED);

    dialview.main.main_1.cont = _cont;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_CENTER, -29, 0);
    LV_FONT_DECLARE(font_bahnschrift_56);
    /*lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);*/
    lv_obj_set_style_text_font(_label, &font_bahnschrift_56, 0);
    lv_label_set_text(_label, "00.00");
    dialview.main.main_1.value_label = _label;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_CENTER, 52, 5);
    LV_FONT_DECLARE(font_bahnschrift_32);
    /*lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);*/
    lv_obj_set_style_text_font(_label, &font_bahnschrift_32, 0);
    lv_label_set_text(_label, "mAh");
    dialview.main.main_1.unit_label = _label;
}

void duration_create(lv_obj_t * par)
{
    lv_obj_t * cont = NULL;
    lv_obj_t * _label = NULL;
    lv_obj_t * _cont = NULL;

    cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    /*lv_obj_add_style(cont, &dialview.main.style, 0);*/
    /*lv_obj_set_style_bg_color(cont,  lv_color_hex(0xE0E0E0), 0);*/
    /*lv_obj_set_style_bg_opa(cont,  LV_OPA_100, 0);*/
    lv_obj_set_size(cont, 170, 25);
    lv_obj_set_pos(cont, 10, 135);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);

    static lv_style_t flex_style;
    lv_style_init(&flex_style);
    lv_style_set_flex_flow(&flex_style, LV_FLEX_FLOW_ROW_WRAP);
    lv_style_set_flex_main_place(&flex_style, LV_FLEX_ALIGN_START);
    lv_style_set_layout(&flex_style, LV_LAYOUT_FLEX);
    lv_style_set_pad_column(&flex_style, 10);
    lv_style_set_pad_row(&flex_style, 0);
    lv_obj_add_style(cont, &flex_style, 0);
    dialview.duration.cont = cont;

    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 40, 25);
    lv_obj_add_style(_cont, &dialview.main.style, 0);
    lv_obj_set_style_radius(_cont, 12, 0);
    lv_obj_set_style_bg_color(_cont,  lv_palette_main(LV_PALETTE_ORANGE), 0);
    lv_obj_set_style_bg_opa(_cont,  LV_OPA_100, 0);
    dialview.duration.title.cont = _cont;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_CENTER, 0, 0);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_color(_label, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(_label, &font_bahnschrift_17, 0);
    lv_label_set_text(_label, "AVG");
    dialview.duration.title.label = _label;

    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 120, 25);
    lv_obj_add_style(_cont, &dialview.main.style, 0);
    lv_obj_set_style_radius(_cont, 12, 0);
    lv_obj_set_style_bg_color(_cont,  lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_obj_set_style_bg_opa(_cont,  LV_OPA_100, 0);

    lv_obj_set_style_bg_color(_cont, lv_palette_main(LV_PALETTE_ORANGE), LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(_cont, lv_color_hex(0xFFFFFF), LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(_cont, lv_palette_main(LV_PALETTE_DEEP_ORANGE), LV_STATE_PRESSED);
    
    dialview.duration.dura.cont = _cont;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_CENTER, -35, 0);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);
    lv_obj_set_style_text_font(_label, &font_bahnschrift_17, 0);
    lv_label_set_text(_label, "TIM");
    dialview.duration.dura.sym_label = _label;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_CENTER, 16, 0);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_color(_label, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(_label, &font_bahnschrift_17, 0);
    lv_label_set_text(_label, "00:00:00");
    dialview.duration.dura.label = _label;
}

void nt_dialplate_count_style_create()
{
    /*Reset style*/
    lv_style_reset(&dialview.count.style);
    lv_style_init(&dialview.count.style);
    lv_style_set_radius(&dialview.count.style, 10);
    lv_style_set_bg_color(&dialview.count.style, lv_color_hex(0xE0E0E0));
    lv_style_set_bg_opa(&dialview.count.style, LV_OPA_100);
    lv_style_set_border_width(&dialview.count.style, 0);
    lv_style_set_border_color(&dialview.count.style, lv_color_hex(0x000000));
    lv_style_set_border_opa(&dialview.count.style, LV_OPA_100);
    lv_style_set_text_color(&dialview.count.style, lv_color_hex(0x000000));
    /*lv_obj_add_style(obj, &dialview.count.style, 0);*/

    /*Reset style*/
    lv_style_reset(&dialview.count.style_points);
    lv_style_init(&dialview.count.style_points);
    lv_style_set_radius(&dialview.count.style_points, 0);
    lv_style_set_bg_color(&dialview.count.style_points, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_opa(&dialview.count.style_points, LV_OPA_100);
    lv_style_set_border_width(&dialview.count.style_points, 0);
    lv_style_set_border_color(&dialview.count.style_points, lv_color_hex(0xFFFFFF));
    lv_style_set_border_opa(&dialview.count.style_points, LV_OPA_100);
    lv_style_set_text_color(&dialview.count.style_points, lv_color_hex(0x000000));
    /*lv_obj_add_style(obj, &dialview.count.style_points, 0);*/
}

void count_create(lv_obj_t * par)
{
    lv_obj_t * _label = NULL;
    lv_obj_t * _cont = NULL;
    lv_obj_t * cont = NULL;
    lv_obj_t * _points = NULL;

    cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_add_style(cont, &dialview.count.style, 0);
    lv_obj_set_size(cont, 120, 150);
    lv_obj_set_pos(cont, 190, 10);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    static lv_style_t flex_style;
    lv_style_init(&flex_style);
    lv_style_set_flex_flow(&flex_style, LV_FLEX_FLOW_ROW);
    lv_style_set_flex_main_place(&flex_style, LV_FLEX_ALIGN_START);
    lv_style_set_layout(&flex_style, LV_LAYOUT_FLEX);
    lv_style_set_pad_column(&flex_style, 2);
    lv_style_set_pad_row(&flex_style, 4);
    lv_obj_add_style(cont, &flex_style, 0);
    dialview.count.cont = cont;

    _points = lv_obj_create(cont);
    lv_obj_remove_style_all(_points);
    lv_obj_set_size(_points, 10, 30);
    lv_obj_add_style(_points, &dialview.count.style_points, 0);
    lv_obj_set_style_bg_color(_points,  lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_radius(_points, 5, 0);

    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 100, 34);
    dialview.count.node_0.cont = _cont;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_TOP_LEFT, 10, 0);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);
    lv_obj_set_style_text_font(_label, &font_bahnschrift_17, 0);
    lv_label_set_text(_label, "current");
    dialview.count.node_0.title_label = _label;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_BOTTOM_LEFT, 10, 0);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x000000), 0);
    lv_obj_set_style_text_font(_label, &font_bahnschrift_17, 0);
    lv_label_set_text(_label, "915.9 mA");
    dialview.count.node_0.value_label = _label;

    _points = lv_obj_create(cont);
    lv_obj_remove_style_all(_points);
    lv_obj_set_size(_points, 10, 30);
    lv_obj_add_style(_points, &dialview.count.style_points, 0);
    lv_obj_set_style_bg_color(_points,  lv_palette_main(LV_PALETTE_PINK), 0);
    lv_obj_set_style_radius(_points, 5, 0);

    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 100, 34);
    dialview.count.node_1.cont = _cont;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_TOP_LEFT, 10, 0);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);
    lv_obj_set_style_text_font(_label, &font_bahnschrift_17, 0);
    lv_label_set_text(_label, "power");
    dialview.count.node_1.title_label = _label;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_BOTTOM_LEFT, 10, 0);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x000000), 0);
    lv_obj_set_style_text_font(_label, &font_bahnschrift_17, 0);
    lv_label_set_text(_label, "915.9 mW");
    dialview.count.node_1.value_label = _label;

    _points = lv_obj_create(cont);
    lv_obj_remove_style_all(_points);
    lv_obj_set_size(_points, 10, 30);
    lv_obj_add_style(_points, &dialview.count.style_points, 0);
    lv_obj_set_style_bg_color(_points,  lv_palette_main(LV_PALETTE_PURPLE), 0);
    lv_obj_set_style_radius(_points, 5, 0);

    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 100, 34);
    dialview.count.node_2.cont = _cont;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_TOP_LEFT, 10, 0);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);
    lv_obj_set_style_text_font(_label, &font_bahnschrift_17, 0);
    lv_label_set_text(_label, "capacity");
    dialview.count.node_2.title_label = _label;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_BOTTOM_LEFT, 10, 0);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x000000), 0);
    lv_obj_set_style_text_font(_label, &font_bahnschrift_17, 0);
    lv_label_set_text(_label, "915.9 mAh");
    dialview.count.node_2.value_label = _label;

    _points = lv_obj_create(cont);
    lv_obj_remove_style_all(_points);
    lv_obj_set_size(_points, 10, 30);
    lv_obj_add_style(_points, &dialview.count.style_points, 0);
    lv_obj_set_style_bg_color(_points,  lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_obj_set_style_radius(_points, 5, 0);

    _cont = lv_obj_create(cont);
    lv_obj_remove_style_all(_cont);
    lv_obj_set_size(_cont, 100, 34);
    dialview.count.node_3.cont = _cont;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_TOP_LEFT, 10, 0);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x3C3C3C), 0);
    lv_obj_set_style_text_font(_label, &font_bahnschrift_17, 0);
    lv_label_set_text(_label, "capacity");
    dialview.count.node_3.title_label = _label;

    _label = lv_label_create(_cont);
    lv_obj_align(_label, LV_ALIGN_BOTTOM_LEFT, 10, 0);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_color(_label, lv_color_hex(0x000000), 0);
    lv_obj_set_style_text_font(_label, &font_bahnschrift_17, 0);
    lv_label_set_text(_label, "915.9 mWh");
    dialview.count.node_3.value_label = _label;
}

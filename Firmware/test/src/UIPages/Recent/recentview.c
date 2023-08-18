/**
 * @file recentview.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "recentview.h"

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
static void chart_create(lv_obj_t * par);
/**********************
 * GLOBAL PROTOTYPES
 **********************/

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

    chart_create(par);
}

static void draw_event_cb(lv_event_t * e)
{
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
    if (!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL))
        return;

    if (dsc->id == LV_CHART_AXIS_PRIMARY_X && dsc->text) {
        const char * month[] = {
            "10", "9", "8", "7", "6", "5", "4", "3", "2", "1"
        };
        lv_snprintf(dsc->text, dsc->text_length, "%s", month[dsc->value]);
    }
}

static void chart_create(lv_obj_t * par)
{
    lv_obj_t * chart = lv_chart_create(recent_view.cont);
    lv_obj_set_size(chart, 250, 100);
    lv_obj_set_pos(chart, 50, 25);
    lv_chart_set_type(chart, LV_CHART_TYPE_BAR);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_chart_set_point_count(chart, 10);
    lv_obj_add_event_cb(chart, draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    recent_view.chart.chart = chart;

    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X,   10, 5, 10, 3, true, 40);
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y,   10, 5, 6,  2, true, 50);
    lv_chart_set_zoom_x(chart, 256);

    lv_chart_series_t * ser = lv_chart_add_series(chart, lv_palette_darken(LV_PALETTE_GREEN, 2), LV_CHART_AXIS_PRIMARY_Y);
    recent_view.chart.ser = ser;

    lv_obj_t * label = lv_label_create(recent_view.cont);
    lv_obj_set_size(label, 30, 20);
    lv_obj_set_pos(label, 20, 3);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_label_set_text_fmt(label, "%s", "mA");
    recent_view.chart.unit_label = label;
}

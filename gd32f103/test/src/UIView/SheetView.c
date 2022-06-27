
#include "SheetView.h"

SheetSence sheetSence;

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

void sheetSenceStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&sheetSence.style);
    lv_style_init(&sheetSence.style);
    lv_style_set_radius(&sheetSence.style, 0);
    lv_style_set_bg_color(&sheetSence.style, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_opa(&sheetSence.style, LV_OPA_100);
    lv_style_set_border_width(&sheetSence.style, 0);
    lv_style_set_border_color(&sheetSence.style, lv_color_hex(0xFFFFFF));
    lv_style_set_border_opa(&sheetSence.style, LV_OPA_100);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&sheetSence.style, lv_color_hex(0x000000));

    lv_obj_add_style(obj, &sheetSence.style, 0);
}

void sheetViewCreate(lv_obj_t * root)
{
    lv_obj_t * cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 320, 170);
    lv_obj_center(cont);
    sheetSenceStyleCreate(cont);
    sheetSenceStyleCreate(root);
    sheetSence.cont = cont;

    lv_obj_t * chart = lv_chart_create(sheetSence.cont);
    lv_obj_set_size(chart, 260, 120);
    lv_obj_set_pos(chart, 50, 10);
    // lv_obj_center(chart);
    lv_chart_set_type(chart, LV_CHART_TYPE_BAR);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_chart_set_point_count(chart, 10);
    lv_obj_add_event_cb(chart, draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    sheetSence.chart = chart;

    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X,   10, 5, 10, 3, true, 40);
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y,   10, 5, 6,  2, true, 50);
    // lv_chart_set_axis_tick(chart, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 3,  4, true, 50);
    lv_chart_set_zoom_x(chart, 256);

    lv_chart_series_t * ser = lv_chart_add_series(chart, lv_palette_darken(LV_PALETTE_GREEN, 2), LV_CHART_AXIS_PRIMARY_Y);
    sheetSence.ser = ser;
}

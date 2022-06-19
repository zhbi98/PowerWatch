
#ifndef __SHEET_VIEW_H__
#define __SHEET_VIEW_H__

#include "lvgl.h"

typedef struct {
    lv_obj_t * cont;
    lv_style_t style;
    lv_obj_t * chart;
    lv_chart_series_t * ser1;
    lv_chart_series_t * ser2;
} SheetSence;

extern SheetSence sheetSence;

extern void sheetViewCreate(lv_obj_t * root);

#endif

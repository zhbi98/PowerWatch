
#include "Sheet.h"

void sheetLoadView(lv_obj_t * root)
{
    lv_obj_set_size(root, MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);
    sheetViewCreate(root);

    sheetAttachEvent(sheetSence.cont);
}

void sheetLoadGroup()
{
    // lv_indev_wait_release(lv_indev_get_act());
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    lv_group_add_obj(group, sheetSence.cont);
}

void sheetAttachEvent(lv_obj_t * obj)
{
    lv_obj_add_event_cb(obj, sheetOnEvent, LV_EVENT_ALL, NULL);
}

void sheetUpdate()
{
    static unsigned int i = 200;
    static unsigned int run = 0;
    if (i == 200) {
        i = 0;
        srand(run);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser1, rand() % 100);

        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);
        lv_chart_set_next_value(sheetSence.chart, sheetSence.ser2, rand() % 300);

        lv_chart_refresh(sheetSence.chart);
    }
    i++;
    run++;
}

void sheetOnEvent(lv_event_t * event)
{
    lv_obj_t * obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == sheetSence.cont) {
        if (code == LV_EVENT_CLICKED) {
            uiViewLoad("About");
        }
    }
}

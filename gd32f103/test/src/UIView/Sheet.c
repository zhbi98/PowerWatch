
#include "Sheet.h"

struct cache_buffer_t bar_cache_buf;

void sheetLoadView(lv_obj_t * root)
{
    lv_obj_set_size(root, MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);
    sheetViewCreate(root);

    sheetAttachEvent(sheetSence.cont);
    sheetAttachEvent(sheetSence.chart);
}

void sheetLoadGroup()
{
    // lv_indev_wait_release(lv_indev_get_act());
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    lv_group_add_obj(group, sheetSence.cont);
    lv_group_add_obj(group, sheetSence.chart);
}

void sheetAttachEvent(lv_obj_t * obj)
{
    lv_obj_add_event_cb(obj, sheetOnEvent, LV_EVENT_ALL, NULL);
}

void bar_cache_hanlder(float value)
{
    cache_typedef cache_data;

    if (cache_full(&bar_cache_buf))
        cache_output(&bar_cache_buf, &cache_data);
    cache_input(&bar_cache_buf, value);
}

void sheetUpdate()
{
    unsigned char index = bar_cache_buf.phead;
    lv_coord_t * chart_array = lv_chart_get_y_array(sheetSence.chart, sheetSence.ser1);

    chart_array[0]  = (int)bar_cache_buf.buf[index];
    index += 3;
    index = index % MAX_BUF_LEN;

    chart_array[1]  = (int)bar_cache_buf.buf[index];
    index += 3;
    index = index % MAX_BUF_LEN;

    chart_array[2]  = (int)bar_cache_buf.buf[index];
    index += 3;
    index = index % MAX_BUF_LEN;

    chart_array[3]  = (int)bar_cache_buf.buf[index];
    index += 3;
    index = index % MAX_BUF_LEN;

    chart_array[4]  = (int)bar_cache_buf.buf[index];
    index += 3;
    index = index % MAX_BUF_LEN;

    chart_array[5]  = (int)bar_cache_buf.buf[index];
    index += 3;
    index = index % MAX_BUF_LEN;

    chart_array[6]  = (int)bar_cache_buf.buf[index];
    index += 3;
    index = index % MAX_BUF_LEN;

    chart_array[7]  = (int)bar_cache_buf.buf[index];
    index += 3;
    index = index % MAX_BUF_LEN;

    chart_array[8]  = (int)bar_cache_buf.buf[index];
    index += 3;
    index = index % MAX_BUF_LEN;

    chart_array[9]  = (int)bar_cache_buf.buf[index];
    index += 3;
    index = index % MAX_BUF_LEN;

    chart_array[10] = (int)bar_cache_buf.buf[index];

    lv_chart_refresh(sheetSence.chart);
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

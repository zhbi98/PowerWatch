/**
 * @file Sheet.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "recent.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void view_load(lv_obj_t * root);
static void view_did_load();
static void view_will_appear();
static void view_did_appear();
static void view_will_disappear();
static void view_did_disappear();
static void view_did_unload();

static void update();
static void ontimer_update();
static void attach_event(lv_obj_t * obj);
static void on_event(lv_event_t * event);

/**********************
 *      TYPEDEFS
 **********************/

const nt_view_t recentview = {
    .load_view           = view_load,
    .view_did_load       = view_did_load,
    .view_will_appear    = view_will_appear,
    .view_did_appear     = view_did_appear,
    .view_will_disappear = view_will_disappear,
    .view_did_disappear  = view_did_disappear,
    .view_will_unload    = NULL,
    .view_did_unload     = view_did_unload,
    .name = "recentview",
};

static struct {
    uint32_t last_update_time;
    lv_timer_t * timer;
} priv;

struct cache_buffer_t bar_cache_buf;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

static void view_load(lv_obj_t * root)
{
    nt_recent_create(root);
    attach_event(recent_view.cont);
}

static void view_did_load()
{

}

static void view_will_appear()
{
    lv_indev_wait_release(lv_indev_get_act());
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    lv_group_add_obj(group, recent_view.cont);
}

static void view_did_appear()
{
    priv.timer = lv_timer_create(ontimer_update, 100, NULL);
}

static void view_will_disappear()
{
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    lv_timer_del(priv.timer);
}

static void view_did_disappear()
{

}

static void view_did_unload()
{

}

static void update()
{
    unsigned char index = bar_cache_buf.phead;
    float range = 0.0;
    lv_coord_t * chart_array = lv_chart_get_y_array(recent_view.chart.chart, recent_view.chart.ser);

    for (unsigned char i = 0; i < 32; i++) {
        if (range <= bar_cache_buf.buf[i])
            range = bar_cache_buf.buf[i];
    }

    // Get unit
    strifica(range, NT_UNIT_CUR);
    // Convert unit
    while (range >= 1000.0)
        range = (float)(range / 1000.0);
    lv_chart_set_range(recent_view.chart.chart, LV_CHART_AXIS_PRIMARY_Y, 0, (int)range + 10);

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

    lv_label_set_text_fmt(recent_view.chart.unit_label, "%s", vstrifica.unit);
    lv_chart_refresh(recent_view.chart.chart);
}

static void ontimer_update()
{
    update();
}

static void attach_event(lv_obj_t * obj)
{
    lv_obj_add_event_cb(obj, on_event, LV_EVENT_ALL, NULL);
}

static void on_event(lv_event_t * event)
{
    lv_obj_t * obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == recent_view.cont) {
        if (code == LV_EVENT_CLICKED) {
            _NT_START_PAGE(infosview);
        }
    }
}

void bar_cache_hanlder(float value)
{
    cache_typedef cache_data;

    if (cache_full(&bar_cache_buf))
        cache_output(&bar_cache_buf, &cache_data);
    cache_input(&bar_cache_buf, value);
}

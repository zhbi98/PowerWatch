/**
 * @file infos.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "infos.h"

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

const nt_view_t infosview = {
    .load_view           = view_load,
    .view_did_load       = view_did_load,
    .view_will_appear    = view_will_appear,
    .view_did_appear     = view_did_appear,
    .view_will_disappear = view_will_disappear,
    .view_did_disappear  = view_did_disappear,
    .view_will_unload    = NULL,
    .view_did_unload     = view_did_unload,
    .name = "infosview",
};

static struct {
    uint32_t last_update_time;
    lv_timer_t * timer;
} priv;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

static void view_load(lv_obj_t * root)
{
    infos_create(root);
    attach_event(infos_view.cont);
}

static void view_did_load()
{

}

static void view_will_appear()
{
    lv_indev_wait_release(lv_indev_get_act());
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    lv_group_add_obj(group, infos_view.cont);
}

static void view_did_appear()
{
    priv.timer = lv_timer_create(
        ontimer_update, 
        1000, 
        NULL
    );
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
    if (
        lv_tick_elaps(
            priv.last_update_time
        ) >= 10
    ) {
        priv.last_update_time = \
            lv_tick_get();
    }
}

static void ontimer_update()
{
    update();
}

static void attach_event(lv_obj_t * obj)
{
    lv_obj_add_event_cb(
        obj, 
        on_event, 
        LV_EVENT_ALL, 
        NULL
    );
}

static void on_event(lv_event_t * event)
{
    lv_obj_t * obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED) {
        _NT_START_PAGE(dialplateview);
    }
}

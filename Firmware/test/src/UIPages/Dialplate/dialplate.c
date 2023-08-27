/**
 * @file dialplate.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "dialplate.h"

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

const nt_view_t dialplateview = {
    .load_view           = view_load,
    .view_did_load       = view_did_load,
    .view_will_appear    = view_will_appear,
    .view_did_appear     = view_did_appear,
    .view_will_disappear = view_will_disappear,
    .view_did_disappear  = view_did_disappear,
    .view_will_unload    = NULL,
    .view_did_unload     = view_did_unload,
    .name = "dialplateview",
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
    nt_dialplate_create(root);
    attach_event(dialview.cont);
    attach_event(dialview.main.main_0.cont);
    attach_event(dialview.main.main_1.cont);
    attach_event(dialview.duration.dura.cont);
}

static void view_did_load()
{

}

static void view_will_appear()
{
    lv_indev_wait_release(lv_indev_get_act());
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    lv_group_add_obj(group, dialview.cont);
    lv_group_add_obj(group, dialview.main.main_0.cont);
    lv_group_add_obj(group, dialview.main.main_1.cont);
    lv_group_add_obj(group, dialview.duration.dura.cont);
}

static void view_did_appear()
{
    priv.timer = lv_timer_create(
        ontimer_update, 
        100, 
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

    strifica(ina226_filte_get_volt(), NT_UNIT_VOLT);
    lv_label_set_text_fmt(dialview.main.main_0.value_label, "%s", vstrifica.value);
    lv_label_set_text_fmt(dialview.main.main_0.unit_label, "%s", vstrifica.unit);

    strifica(_filte_get_volt(), NT_UNIT_VOLT);
    lv_label_set_text_fmt(dialview.main.main_1.value_label, "%s", vstrifica.value);
    lv_label_set_text_fmt(dialview.main.main_1.unit_label, "%s", vstrifica.unit);

    lv_label_set_text_fmt(dialview.duration.dura.label, "%02d:%02d:%02d", 
        qflow_dura_get_hour(),
        qflow_dura_get_min(),
        qflow_dura_get_sec()
    );

    strifica(ina226_filte_get_cur(), NT_UNIT_CUR);
    lv_label_set_text_fmt(dialview.count.node_0.value_label, "%s", vstrifica.full);

    strifica(ina226_filte_get_pow(), NT_UNIT_POW);
    lv_label_set_text_fmt(dialview.count.node_1.value_label, "%s", vstrifica.full);

    strifica(QFLOW_GET_MAH(), NT_UNIT_MAH);
    lv_label_set_text_fmt(dialview.count.node_2.value_label, "%s", vstrifica.full);

    strifica(QFLOW_GET_MWH(), NT_UNIT_MWH);
    lv_label_set_text_fmt(dialview.count.node_3.value_label, "%s", vstrifica.full);
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

#define CLICKED  LV_EVENT_CLICKED
#define PRESSED  LV_EVENT_LONG_PRESSED

#define MODULE_0 dialview.cont
#define MODULE_1 dialview.main.main_0.cont
#define MODULE_2 dialview.main.main_1.cont
#define MODULE_3 dialview.duration.dura.cont

static void on_event(lv_event_t * event)
{
    lv_obj_t * obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == MODULE_0) {
        if (code == CLICKED) {
            _NT_START_PAGE(recentview);
        }
        if (code == PRESSED) {

        }
    } 

    if (obj == MODULE_1) {
        if (code == CLICKED) {

        }
        if (code == PRESSED) {

        }
    } 

    if (obj == MODULE_2) {
        if (code == CLICKED) {

        }
        if (code == PRESSED) {

        }
    } 

    if (obj == MODULE_3) {
        if (code == CLICKED) {

        }
        if (code == PRESSED) {

        }
    }
}

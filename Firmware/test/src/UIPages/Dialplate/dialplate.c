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

DisplayMode displayMode = {
    .cont1_mode = 0,
    .cont2_mode = 0,
};

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

static lv_timer_t * update_handle;
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
    update_handle = lv_timer_create(ontimer_update, 100, NULL);
}

static void view_will_disappear()
{
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    lv_timer_del(update_handle);
}

static void view_did_disappear()
{

}

static void view_did_unload()
{

}

static void update()
{
    switch (displayMode.cont1_mode) {
    case 0:
        strifica(ina226_data.voltageVal, NT_UNIT_VOLT);
        break;
    case 1:
        strifica(ina226_data.Shunt_Current, NT_UNIT_CUR);
        break;
    case 2:
        strifica(ina226_data.Power, NT_UNIT_POW);
        break;
    }
    lv_label_set_text_fmt(dialview.main.main_0.value_label, "%s", vstrifica.value);
    lv_label_set_text_fmt(dialview.main.main_0.unit_label, "%s", vstrifica.unit);

    switch (displayMode.cont2_mode) {
    case 0:
        strifica(average_calc.average, NT_UNIT_VOLT);
        break;
    case 1:
        strifica(average_calc.average, NT_UNIT_CUR);
        break;
    case 2:
        strifica(average_calc.average, NT_UNIT_POW);
        break;
    }
    lv_label_set_text_fmt(dialview.main.main_1.value_label, "%s", vstrifica.value);
    lv_label_set_text_fmt(dialview.main.main_1.unit_label, "%s", vstrifica.unit);

    uint8_t buf[15];
    memset(buf, '\0', 15);
    int32_t hour = (int32_t)(get_elec_calc_time()) / 3600;
    int32_t min  = (int32_t)(get_elec_calc_time()) % 3600 / 60;
    int32_t sec  = (int32_t)(get_elec_calc_time()) % 3600 % 60;
    snprintf(buf, 13, "%02d:%02d:%02d", hour, min, sec);
    lv_label_set_text_fmt(dialview.duration.dura.label, "%s", buf);

    switch (displayMode.cont1_mode) {
    case 0:
        strifica(ina226_data.Shunt_Current, NT_UNIT_CUR);
        break;
    case 1:
        strifica(ina226_data.voltageVal, NT_UNIT_VOLT);
        break;
    case 2:
        strifica(ina226_data.Shunt_Current, NT_UNIT_CUR);
        break;
    }
    lv_label_set_text_fmt(dialview.count.node_0.value_label, "%s", vstrifica.full);

    switch (displayMode.cont1_mode) {
    case 0:
        strifica(ina226_data.Power, NT_UNIT_POW);
        break;
    case 1:
        strifica(ina226_data.Power, NT_UNIT_POW);
        break;
    case 2:
        strifica(ina226_data.voltageVal, NT_UNIT_VOLT);
        break;
    }
    lv_label_set_text_fmt(dialview.count.node_1.value_label, "%s", vstrifica.full);

    strifica(get_elec_calc_mah(), NT_UNIT_MAH);
    lv_label_set_text_fmt(dialview.count.node_2.value_label, "%s", vstrifica.full);
    strifica(get_elec_calc_mwh(), NT_UNIT_MWH);
    lv_label_set_text_fmt(dialview.count.node_3.value_label, "%s", vstrifica.full);
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

    if (obj == dialview.cont) {
        if (code == LV_EVENT_CLICKED) {
            _NT_START_PAGE(recentview);
        }
    } else if (obj == dialview.main.main_0.cont) {
        if (code == LV_EVENT_CLICKED) {
            displayMode.cont1_mode++;
            if (displayMode.cont1_mode > 2)
                displayMode.cont1_mode = 0;
        }
    } else if (obj == dialview.main.main_1.cont) {
        if (code == LV_EVENT_CLICKED) {
            displayMode.cont2_mode++;
            if (displayMode.cont2_mode > 2)
                displayMode.cont2_mode = 0;
            average_calc_reset();
        }
    } else if (obj == dialview.duration.dura.cont) {
        if (code == LV_EVENT_CLICKED) {
            if (!get_elec_status())
                set_elec_status(1);
            else
                set_elec_status(0);
        } else if (code == LV_EVENT_LONG_PRESSED) {
            elec_calc_clear();
        }
    }
}

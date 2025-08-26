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

#define CONFIG_DIAL_TIMER_PERIOD 100 /*200ms*/
#define CONFIG_DIAL_REFR_PERIOD0 100 /*100ms*/
#define CONFIG_DIAL_REFR_PERIOD1 100 /*100ms*/

/**********************
 *  STATIC VARIABLES
 **********************/

static bool inited = false;

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

/**
 * The page does not exist, and you need to perform a page 
 * load operation to create a new page.
 */
static void view_load(lv_obj_t * root)
{
    nt_dialplate_create(root);
    attach_event(dialview.cont);
    attach_event(dialview.main.main_0.cont);
    attach_event(dialview.main.main_1.cont);
    attach_event(dialview.duration.dura.cont);
}

/**
 * The page does not exist, and you need to perform a page 
 * load operation to create a new page.
 */
static void view_did_load()
{
    /*The page is loaded*/
}

/**
 * Will appear callback function, will appear.
 */
static void view_will_appear()
{
    lv_indev_wait_release(lv_indev_get_act());
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    lv_group_add_obj(group, dialview.cont);
    lv_group_add_obj(group, dialview.main.main_0.cont);
    lv_group_add_obj(group, dialview.main.main_1.cont);
    lv_group_add_obj(group, dialview.duration.dura.cont);

    nt_load_anim_t _amin = LOAD_ANIM_MOVE_TOP;

    if (!inited) {
        _amin = LOAD_ANIM_FADE_ON;
        inited = true;
    }

    nt_pm_loadanim_set_custom_type(
        _amin, 400, 
        lv_anim_path_ease_out
    );
}

/**
 * Did appear callback function, did appear.
 */
static void view_did_appear()
{
    /*The loaded page is already displayed*/
    priv.timer = lv_timer_create(
        ontimer_update, 
        CONFIG_DIAL_TIMER_PERIOD, 
        NULL);
}

/**
 * Will disappear callback function, will disappear.
 */
static void view_will_disappear()
{
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);
    lv_timer_del(priv.timer);

    nt_pm_loadanim_set_custom_type(
        LOAD_ANIM_MOVE_TOP, 400, 
        lv_anim_path_ease_out
    );
}

/**
 * Did disappear callback function, did disappear.
 */
static void view_did_disappear()
{
    /*The loaded page is already disappeared*/
}

/**
 * Unload callback function, unload page.
 */
static void view_did_unload()
{
    /**
     * The Page's cache will be released, 
     * and if the page contains dynamic 
     * resources, release them manually
     * under this function
     */
}

static void update()
{
    if (
        lv_tick_elaps(
            priv.last_update_time
        ) >= CONFIG_DIAL_REFR_PERIOD0
    ) {
        priv.last_update_time = \
            lv_tick_get();
    }

    strifica(ina226_filte_get_volt(), NT_UNIT_VOLT);
    lv_label_set_text_fmt(dialview.main.main_0.value_label, "%s", vstrifica.value);
    lv_label_set_text_fmt(dialview.main.main_0.unit_label, "%s", vstrifica.unit);

    strifica(avg_filte_get_volt(), NT_UNIT_VOLT);
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
    lv_obj_add_event_cb(obj, on_event, 
        LV_EVENT_ALL, NULL);
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

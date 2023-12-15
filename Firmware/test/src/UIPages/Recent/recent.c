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

#define CONFIG_RECENT_TIMER_PERIOD 100 /*200ms*/
#define CONFIG_RECENT_REFR_PERIOD0 100 /*100ms*/
#define CONFIG_RECENT_REFR_PERIOD1 100 /*100ms*/

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

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * The page does not exist, and you need to perform a page 
 * load operation to create a new page.
 */
static void view_load(lv_obj_t * root)
{
    nt_recent_create(root);
    attach_event(recent_view.cont);
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

    lv_group_add_obj(group, recent_view.cont);

    nt_pm_loadanim_set_custom_type(
        LOAD_ANIM_MOVE_TOP, 400, 
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
        CONFIG_RECENT_TIMER_PERIOD, 
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

    if (obj == recent_view.cont) {
        if (code == LV_EVENT_CLICKED) {
            _NT_START_PAGE(infosview);
        }
    }
}

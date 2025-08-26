/**
 * @file nt_pm.h
 *
 */

#ifndef __NT_PM_H__
#define __NT_PM_H__

/*********************
 *      INCLUDES
 *********************/

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "lvgl.h"
#include "nt_qq.h"
#include "log.h"
#include "nt_anim.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Construct a view type*/
typedef struct {
    void (* load_view)(lv_obj_t * root);

    void (* view_did_load)(void);

    void (* view_will_appear)(void);

    void (* view_did_appear)(void);

    void (* view_will_disappear)(void);

    void (* view_did_disappear)(void);

    void (* view_will_unload)(void);

    void (* view_did_unload)(void);

    uint8_t name[16];
} nt_view_t;

typedef enum {
    NT_STATE_IDLE = 0x01,
    NT_STATE_LOAD = 0x02,
    NT_STATE_DIDLOAD = 0x03,
    NT_STATE_WILLAPPEAR = 0x04,
    NT_STATE_DIDAPPEAR = 0x05,
    NT_STATE_ACTIVITY = 0x06,
    NT_STATE_WILLDISAPPEAR = 0x07,
    NT_STATE_DIDDISAPPEAR = 0x08,
    NT_STATE_UNLOAD = 0x09,
} nt_state_t;

/*Construct a page type*/
typedef struct {
    lv_obj_t * root;
    nt_state_t state;
    uint8_t name[16];
    uint16_t idx;

    /*Private data, Only page manager access*/
    struct {
        bool is_disable_auto_cache; /**< Automatic cache management*/
        bool is_cached; /**< Cache enable*/
        /*Animation state*/
        struct {
            bool is_enter;           /** <Whether it is the entering party*/
            bool is_busy;            /** <Whether the animation is playing*/
            anim_attr_t attr;        /** <Animation properties*/
        } anim;
    } priv;
} nt_page_t;

/**
 * NT error codes.
 */
enum {
    NT_RES_INV = 0, /*Typically indicates that the object is deleted (become invalid) in the action
                      function or an operation was failed*/
    NT_RES_OK,      /*The object is valid (no deleted) after the action*/
};
typedef uint8_t nt_res_t;

#define NT_ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/**********************
 * GLOBAL PROTOTYPES
 **********************/

uint8_t _nt_view_pointer_init(const nt_view_t * view_p);
uint16_t nt_pm_get_num_of_init_view();
uint8_t nt_pm_name_get_view_id(uint8_t * name, uint16_t * idx);
uint8_t _nt_buffer_node_move_back(nt_page_t * pages_p, uint16_t * idx);
uint8_t nt_pm_name_get_page_id(uint8_t * name, uint16_t * idx);
uint16_t nt_pm_get_num_of_bg_page();
nt_res_t nt_start_page(uint8_t * name);
void nt_page_state_update(nt_page_t * page_p);
nt_state_t nt_state_load_execute(nt_page_t * page_p);
nt_state_t nt_state_will_appear_execute(nt_page_t * page_p);
nt_state_t nt_state_did_appear_execute(nt_page_t * page_p);
nt_state_t nt_state_will_disappear_execute(nt_page_t * page_p);
nt_state_t nt_state_did_disappear_execute(nt_page_t * page_p);
nt_state_t nt_state_unload_execute(nt_page_t * page_p);

#define _NT_START_PAGE(_name) \
    nt_start_page(#_name)

/**
 * Structure for holding page animation state.
 * Manages the state of the page scheduler.
 */
typedef struct {
    bool is_switch_req; /**< Whether to rotations request*/
    bool is_busy;       /**< Is rotation*/
    bool is_pushing;    /**< Whether it is in push state*/

    anim_attr_t current;
    anim_attr_t global; 
} nt_anim_state_t;

void nt_pm_view_rotations_anim_create(nt_page_t * page_p);
void nt_pm_anim_default_init(lv_anim_t * a);
void nt_pm_view_rotations_anim_finish(lv_anim_t * a);

void nt_pm_loadanim_set_custom_type(uint8_t anim_type, 
    uint16_t time, lv_anim_path_cb_t path);
nt_load_anim_t nt_pm_loadanim_get_current_type();
bool nt_pm_loadanim_get_current_attr(load_anim_attr_t * attr);

#endif /*NT_PM_H*/

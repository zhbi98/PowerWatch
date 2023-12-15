/**
 * @file nt_act.h
 *
 */

#ifndef __NT_ACT_H__
#define __NT_ACT_H__

/*********************
 *      INCLUDES
 *********************/

#include "statbarview.h"
#include "log.h"
#include "lvgl.h"
#include "nt_pm.h"
#include <string.h>

/*********************
 *      DEFINES
 *********************/

/* Dynamic island Default pos and size */
#define SYM_GAP_DEF    4U
#define SYM_END_DEF    317U

/**********************
 *      TYPEDEFS
 **********************/

/**
 * An activity that can be run in dynamic island.
 */
enum {
    NT_ACTIVE_TIME = 0,
    NT_ACTIVE_USB,
    NT_ACTIVE_TIMER,
    NT_ACTIVE_SOUND,
    NT_ACTIVE_BATTERY,
    _NT_ACTIVE_LAST
};
typedef uint8_t nt_active_symbol_t;

/**
 * Descriptor a active ui indicator/area, 
 * area_update.
 */
typedef struct {
    lv_coord_t x;
    lv_coord_t y;
    lv_coord_t w;
    lv_coord_t h;
} nt_active_area_t;

/**
 * Describes the information contained 
 * in an activity.
 */
typedef struct {
    uint16_t act_id; /**< Specify a number for the activity*/
    uint8_t act_name[8]; /**< Specify a nameactivity*/
    uint8_t act_pri; /**< The weight of the activity*/
} nt_active_desc_t;

/**
 * Descriptor a activity
 * object.
 */
typedef struct {
    uint16_t idx; /**< Index of active desc in the registry*/
    bool anim;
    uint8_t name[8];
    bool isact;
} nt_active_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * The activity descriptor is registered in the 
 * cache and can then be used to start the 
 * associated device symbol.
 * @param desc_p pointer to an initialized 
 * 'nt_active_desc_t' variable.
 * @return initialized result.
 */
uint8_t _nt_active_desc_register(
    const nt_active_desc_t * desc_p);

/**
 * Gets the number of registered activity descriptors.
 * @return number of registered descriptors.
 */
uint16_t nt_active_get_register_cnt();

/**
 * Gets the index of the active from the active name string.
 * @param name pointer to active name.
 * @param idx gets the result of the name.
 * @return convert result.
 */
uint8_t nt_active_name_get_id(
    uint8_t * name, uint16_t * idx);

/**
 * Gets the display size of the active symbol that can be used for 
 * subsequent dynamic display coordinate calculations.
 * @param act_sym active symbol name.
 * @return symbol width.
 */
uint16_t nt_active_get_symbol_size(
    nt_active_symbol_t act_sym);

/**
 * Gets the index of the active from the active name string.
 * @param name pointer to active name.
 * @param idx gets the result of the name.
 * @return convert result.
 */
uint8_t nt_active_name_get_act_id(uint8_t * name, 
    uint16_t * idx);

/**
 * Gets the number of activities that have 
 * been cached in the active cache.
 * @return number of cached active.
 */
uint16_t nt_active_get_active_cnt();

/**
 * Start the active with the name, start new active, 
 * update the active cached.
 * @param name active name.
 * @return start result.
 */
nt_res_t nt_start_active(uint8_t * name);

/**
 * Remove the active with the name, remove a active, 
 * update the active cached.
 * @param name active name.
 * @return start result.
 */
nt_res_t nt_remove_active(uint8_t * name);

/**
 * Clears the closed activity from the activity cache.
 */
void nt_active_clean_node();

/**
 * The active node objects that are already active are prioritized.
 */
void nt_active_filte_act_node();

/**
 * Gets the number of activities that have been filted 
 * in the active cache.
 * @return number of filted active.
 */
uint16_t nt_active_get_filted_cnt();

/**
 * Extract the three highest priority activities from each of 
 * the activity caches and add them to the filter list.
 */
void nt_active_filte_node();

/**
 * Reset the status of the active symbol, update the status 
 * of the active symbol, 
 * perform recommendations, calculate 
 * the position of the active symbol, 
 * update the active bar and so on.
 */
void nt_active_update();

/**
 * Registers the defined event object with 
 * the recommendation engine.
 */
void nt_active_desc_init();

#define _NT_START_ACT(_name) \
    nt_start_active(#_name)

#define _NT_RM_ACT(_name) \
    nt_remove_active(#_name)

/**
 * Set the activity manager to run in 
 * select or recommended mode.
 * @param mod active running mode.
 */
void nt_active_set_mode(uint8_t mod);

/**
 * Gets the current state of the specified activity 
 * by the activity name.
 * @param name active name.
 */
bool nt_active_get_state(uint8_t * name);

#define _NT_STATE_ACT(_name) \
    nt_active_get_state(#_name)

#endif /*__NT_ACT_H__*/

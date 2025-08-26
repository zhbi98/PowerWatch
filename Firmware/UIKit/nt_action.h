/**
 * @file nt_action.h
 *
 */

#ifndef __NT_ACTION_H__
#define __NT_ACTION_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "log.h"

/*********************
 *      DEFINES
 *********************/

#define DEPTH 1
#define GROUP 3

/**********************
 *      TYPEDEFS
 **********************/

typedef void (*_disp_cb_t)(uint8_t, void *);
typedef void (*_event_cb_t)(uint8_t, void *);

/*Construct a action group type*/
typedef struct {
    _disp_cb_t disp_cb;      /**< NT Action to the display*/
    _event_cb_t event_cb[4]; /**< NT Action event*/
    uint8_t valid[4];
} _action_group_t;

/*Construct a NT action type*/
typedef struct {
    _action_group_t allgroup[DEPTH][GROUP]; /**< All groups that make up an action*/
    _action_group_t actgroup; /**< The currently active group*/
    uint16_t depth;
    uint16_t group;
    bool need_flush; /**< Whether the active grouping needs to be drawn to the screen*/
} nt_action_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void nt_action_group_init(nt_action_t * act_p);
void nt_action_default_set(nt_action_t * act_p);
void nt_action_refresh(nt_action_t * act_p);
void nt_action_set_depth(nt_action_t * act_p, uint16_t depth);
void nt_action_set_group(nt_action_t * act_p, uint16_t group);
void nt_action_event_send(nt_action_t * act_p, uint16_t id, 
    uint8_t code, void * param);
void nt_action_disp_flush(nt_action_t * act_p, uint8_t code, void * param);
void nt_action_add_group(nt_action_t * act_p, uint16_t depth, 
    uint16_t group, _action_group_t * actgroup);
void nt_action_disp_enable_flush(nt_action_t * act_p);
bool nt_action_disp_need_flush(nt_action_t * act_p);
void nt_action_set_event_valid(nt_action_t * act_p, uint16_t id, bool valid);
bool nt_action_get_event_valid(nt_action_t * act_p, uint16_t id);

#endif /*__NT_ACTION_H__*/

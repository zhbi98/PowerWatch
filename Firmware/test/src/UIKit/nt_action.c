/**
 * @file nt_action.c
 *
 */

#include "nt_action.h"

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void _default_disp_cb(uint8_t code, void * param);
static void _default_event_cb(uint8_t code, void * param);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize a NT action with default values.
 * It is used to have known values in the fields and not junk in memory.
 * After it you can safely set only the fields you need.
 * @param act_p pointer to NT action variable to initialize
 */
void nt_action_group_init(nt_action_t * act_p)
{
    _action_group_t * group  = NULL;
    _disp_cb_t disp_cb   = _default_disp_cb;
    _event_cb_t event_cb = _default_event_cb;

    act_p->actgroup.disp_cb = disp_cb;

    for (uint16_t node = 0; node < 4; node++) {
        act_p->actgroup.event_cb[node] = event_cb;
        act_p->actgroup.valid[node] = true;
    }

    for (uint16_t dep = 0; dep < DEPTH; dep++) {
        for (uint16_t grp = 0; grp < GROUP; grp++) {
            group = &act_p->allgroup[dep][grp];
            for (uint16_t node = 0; node < 4; node++) {
                group->event_cb[node] = event_cb;
                group->valid[node] = true;
            }
            group->disp_cb = disp_cb;
        }
    }

    act_p->need_flush = true;
    act_p->depth = 0;
    act_p->group = 0;
}

/**
 * Set a action's depth and group to default.
 * @param act_p pointer to NT action variable to initialize
 */
void nt_action_default_set(nt_action_t * act_p)
{
    act_p->need_flush = true;
    act_p->depth = 0;
    act_p->group = 0;

    nt_action_refresh(act_p);
}

/**
 * Refreshes the currently active grouping for displaying or executing callback functions.
 * @param act_p pointer to an NT action.
 */
void nt_action_refresh(nt_action_t * act_p)
{
    uint16_t dep = act_p->depth;
    uint16_t grp = act_p->group;

    if (dep > DEPTH) return;
    if (grp > GROUP) return;

    memcpy(&act_p->actgroup, 
        &act_p->allgroup[dep][grp], 
        sizeof(_action_group_t));
}

/**
 * Sets the depth of the NT action to activate different groups of NT action
 * @param act_p pointer to an NT action.
 * @param depth.
 */

void nt_action_set_depth(nt_action_t * act_p, uint16_t depth)
{
    if (depth > DEPTH) return;
    act_p->depth = depth;
    nt_action_refresh(act_p);

    act_p->need_flush = true;
}

/**
 * Sets the group of the NT action to activate different groups of NT action
 * @param act_p pointer to an NT action.
 * @param group.
 */
void nt_action_set_group(nt_action_t * act_p, uint16_t group)
{
    if (group > GROUP) return;
    act_p->group = group;
    nt_action_refresh(act_p);

    act_p->need_flush = true;
}

/**
 * Sends events and parameters to the unit specified in the NT action.
 * @param act_p pointer to an NT action.
 * @param id unit's id.
 * @param code event code.
 * @param param additional param.
 */
void nt_action_event_send(nt_action_t * act_p, uint16_t id, uint8_t code, void * param)
{
    if (id > 4) return;

    nt_action_refresh(act_p);

    _event_cb_t event_cb = act_p->actgroup.event_cb[id];

    if (!act_p->actgroup.valid[id]) return;

    event_cb(code, param);
}

/**
 * Sends events and parameters to the unit specified in the NT action.
 * @param act_p pointer to an NT action.
 * @param code.
 * @param param.
 */
void nt_action_disp_flush(nt_action_t * act_p, uint8_t code, void * param)
{
    if (!act_p->need_flush) return;

    nt_action_refresh(act_p);

    _disp_cb_t disp_cb = act_p->actgroup.disp_cb;

    disp_cb(code, param);

    act_p->need_flush = false;
}

/**
 * Adds A event group to the NT action.
 * @param act_p pointer to an NT action.
 * @param depth.
 * @param group.
 * @param actgroup.
 */
void nt_action_add_group(nt_action_t * act_p, uint16_t depth, 
    uint16_t group, _action_group_t * actgroup)
{
    if (depth > DEPTH) return;
    if (group > GROUP) return;

    _action_group_t * grp = &act_p->allgroup[depth][group];
    memcpy(grp, actgroup, sizeof(_action_group_t));

    nt_action_refresh(act_p);
}

/**
 * Enable content updates.
 * @param act_p pointer to an NT action.
 */
void nt_action_disp_enable_flush(nt_action_t * act_p)
{
    act_p->need_flush = true;
}

/**
 * Whether the active grouping needs to be drawn to the screen.
 * @param act_p pointer to an NT action.
 */
bool nt_action_disp_need_flush(nt_action_t * act_p)
{
    return act_p->need_flush;
}

/**
 * Set the validity of the specified event.
 * @param act_p pointer to an NT action.
 * @id event id.
 * @valid event validity.
 */
void nt_action_set_event_valid(nt_action_t * act_p, uint16_t id, bool valid)
{
    if (id > 4) return;

    uint16_t dep = act_p->depth;
    uint16_t grp = act_p->group;

    if (dep > DEPTH) return;
    if (grp > GROUP) return;

    act_p->allgroup[dep][grp].valid[id] = valid;

    nt_action_refresh(act_p);
}

/**
 * The callback function is displayed by default.
 * @param code event code.
 * @param param reserve entry for passing private parameters.
 */
static void _default_disp_cb(uint8_t code, void * param)
{
    info("Invalid NT disp callback");
}

/**
 * The callback function is event by default.
 * @param code pointer to an NT action.
 * @param param reserve entry for passing private parameters.
 */
static void _default_event_cb(uint8_t code, void * param)
{
    info("Invalid NT event callback");
}

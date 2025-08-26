/**
 * @file nt_pm.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "nt_pm.h"

/**********************
 *      TYPEDEFS
 **********************/

const nt_view_t * views[5] = {0};
uint16_t view_cnt = 0;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Register an initialized view pointer, the pointers are injected into the view buffer sequentially.
 * @param view_p pointer to an initialized 'nt_view_t' variable. Only its pointer is saved!
 * @return initialized result.
 */
uint8_t _nt_view_pointer_init(const nt_view_t * view_p)
{
    uint16_t size = NT_ARR_SIZE(views);

    if (view_cnt > size - 1) return NT_RES_INV;
    views[view_cnt] = view_p;
    view_cnt++;

    return NT_RES_OK;
}

/**
 * Gets the number of initialized view.
 * @return number of initialized view.
 */
uint16_t nt_pm_get_num_of_init_view()
{
    return view_cnt;
}

/**
 * Gets the index of the view from the view name string.
 * @param name pointer to view name.
 * @param idx gets the result of the name.
 * @return convert result.
 */
uint8_t nt_pm_name_get_view_id(uint8_t * name, uint16_t * idx)
{
    uint16_t size = NT_ARR_SIZE(views);
    for (uint16_t i = 0; i < size; i++) {
        if (!strcmp(views[i]->name, name)) {
            *idx = i;
            return NT_RES_OK;
        }
    }
    return NT_RES_INV;
}

nt_page_t pages[4] = {0};
uint16_t page_cnt = 0;

/**
 * Moves the nodes before the specified position backward in sequence.
 * @param pages_p pointer to an 'nt_page_t' buffer.
 * @param idx position.
 * @return move back result.
 */
uint8_t _nt_buffer_node_move_back(nt_page_t * pages_p, uint16_t * idx)
{
    uint16_t size = NT_ARR_SIZE(pages);
    if (*idx > (size - 1)) return NT_RES_INV;

    for (uint16_t i = *idx; i > 0; i--) pages_p[i] = pages_p[i - 1];

    memset(&pages_p[0], 0, sizeof(nt_page_t));

    return NT_RES_OK;
}

/**
 * Gets the index of the page from the page name string.
 * @param name pointer to page name.
 * @param idx gets the result of the name.
 * @return convert result.
 */
uint8_t nt_pm_name_get_page_id(uint8_t * name, uint16_t * idx)
{
    uint16_t size = NT_ARR_SIZE(pages);
    for (uint8_t i = 0; i < size; i++) {
        if (!strcmp(pages[i].name, name)) {
            *idx = i;
            return NT_RES_OK;
        }
    }
    return NT_RES_INV;
}

/**
 * Gets the number of background page in the buffer.
 * @return number of background page.
 */
uint16_t nt_pm_get_num_of_bg_page()
{
    return page_cnt;
}

uint16_t prev = 0xFFFF;
nt_anim_state_t anim_state;

/**
 * Start the page with the name, start new page, update the status information of the old page.
 * @param name page name.
 * @return start result.
 */
nt_res_t nt_start_page(uint8_t * name)
{
    uint16_t act_view_idx;
    uint16_t act_page_idx;
    uint16_t t_idx;
    uint16_t deep;

    deep = NT_ARR_SIZE(pages);

    /*Call the ancestor's view handler*/
    nt_res_t res = nt_pm_name_get_view_id(name, &act_view_idx);

    if(res != NT_RES_OK || anim_state.is_switch_req)
        return NT_RES_INV;

    /*The page scheduler is executing a 
    switch request for a page*/
    anim_state.is_switch_req = true;

    /*Prevent duplicate scheduling of pages*/
    if (act_view_idx == prev)
        return NT_RES_OK;

    /*Cache the page idx*/
    prev = act_view_idx;

    /*Call the page buffer*/
    res = nt_pm_name_get_page_id(name, &act_page_idx);

    /*Need create a new page to buffer*/
    if(res != NT_RES_OK) {
        if (page_cnt == deep) {
            nt_page_t t_page;
            memcpy(&t_page, &pages[deep - 1], sizeof(nt_page_t));
            t_idx = deep - 1;
            _nt_buffer_node_move_back(pages, &t_idx);
            pages[0].root = NULL;
            pages[0].state = NT_STATE_LOAD;
            strncpy(pages[0].name, name, 16);
            pages[0].idx = act_view_idx;
            page_cnt = deep;
            lv_obj_del_async(t_page.root);
        } else {
            t_idx = deep - 1;
            _nt_buffer_node_move_back(pages, &t_idx);
            pages[0].root = NULL;
            pages[0].state = NT_STATE_LOAD;
            strncpy(pages[0].name, name, 16);
            pages[0].idx = act_view_idx;
            page_cnt++;
        }
    } else {
        nt_page_t act_page;
        memcpy(&act_page, &pages[act_page_idx], sizeof(nt_page_t));
        _nt_buffer_node_move_back(pages, &act_page_idx);
        memcpy(&pages[0], &act_page, sizeof(nt_page_t));
        pages[0].state = NT_STATE_WILLAPPEAR;
    }

    if (pages[1].root != NULL) pages[1].priv.anim.is_enter = false;
    pages[0].priv.anim.is_enter = true;

    anim_state.is_pushing = false;

    if (anim_state.is_pushing) {}

    /*Update status information for new and old pages*/
    nt_page_state_update(&pages[1]);
    nt_page_state_update(&pages[0]);

    /*bool is_pushing = true;*/

    if (anim_state.is_pushing) {
        if (pages[1].root) lv_obj_move_foreground(pages[1].root);
        lv_obj_move_foreground(pages[0].root);
    } else {
        lv_obj_move_foreground(pages[0].root);
        if (pages[1].root) lv_obj_move_foreground(pages[1].root);
    }

    return NT_RES_OK;
}

/**
 * Update the status information of the page, 
 * according to the current state of the page to determine the next state.
 * @param page_p pointer to an 'nt_page_t' page.
 */
void nt_page_state_update(nt_page_t * page_p)
{
    if (page_p == NULL) return;
    switch (page_p->state) {
    case NT_STATE_IDLE:
        break;
    case NT_STATE_LOAD:
        page_p->state = nt_state_load_execute(page_p);
        nt_page_state_update(page_p);
        break;
    case NT_STATE_WILLAPPEAR:
        page_p->state = nt_state_will_appear_execute(page_p);
        /*nt_page_state_update(page_p);*/
        break;
    case NT_STATE_DIDAPPEAR:
        page_p->state = nt_state_did_appear_execute(page_p);
        break;
    case NT_STATE_ACTIVITY:
        page_p->state = NT_STATE_WILLDISAPPEAR;
        nt_page_state_update(page_p);
        break;
    case NT_STATE_WILLDISAPPEAR:
        page_p->state = nt_state_will_disappear_execute(page_p);
        /*nt_page_state_update(page_p);*/
        break;
    case NT_STATE_DIDDISAPPEAR:
        page_p->state = nt_state_did_disappear_execute(page_p);
        if (page_p->state == NT_STATE_UNLOAD)
            nt_page_state_update(page_p);
        break;
    case NT_STATE_UNLOAD:
        page_p->state = nt_state_unload_execute(page_p);
        break;
    }
}

/**
 * The page does not exist, and you need to perform a page load operation to create a new page.
 * @param page_p pointer to an 'nt_page_t' page.
 * @return next state.
 */
nt_state_t nt_state_load_execute(nt_page_t * page_p)
{
    /*If a page needs to be created, then the page has 
      not been created or released*/
    if (page_p->root != NULL) {
        /*info("Root must be NULL");*/
    }

    lv_obj_t * root_obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(root_obj, 320, 240);
    lv_obj_clear_flag(root_obj, LV_OBJ_FLAG_SCROLLABLE);
    page_p->root = root_obj;
    views[page_p->idx]->load_view(page_p->root);
    views[page_p->idx]->view_did_load();

    if (page_p->priv.is_disable_auto_cache)
        page_p->priv.is_cached = false;
    else page_p->priv.is_cached = true;

    return NT_STATE_WILLAPPEAR;
}

/**
 * Will appear callback function, will appear.
 * @param page_p pointer to an 'nt_page_t' page.
 * @return next state.
 */
nt_state_t nt_state_will_appear_execute(nt_page_t * page_p)
{
    views[page_p->idx]->view_will_appear();
    lv_obj_clear_flag(page_p->root, LV_OBJ_FLAG_HIDDEN);
    nt_pm_view_rotations_anim_create(page_p);
    return NT_STATE_DIDAPPEAR;
}

/**
 * Did appear callback function, did appear.
 * @param page_p pointer to an 'nt_page_t' page.
 * @return next state.
 */
nt_state_t nt_state_did_appear_execute(nt_page_t * page_p)
{
    views[page_p->idx]->view_did_appear();
    return NT_STATE_ACTIVITY;
}

/**
 * Will disappear callback function, will disappear.
 * @param page_p pointer to an 'nt_page_t' page.
 * @return next state.
 */
nt_state_t nt_state_will_disappear_execute(nt_page_t * page_p)
{
    views[page_p->idx]->view_will_disappear();
    nt_pm_view_rotations_anim_create(page_p);
    return NT_STATE_DIDDISAPPEAR;
}

/**
 * Did disappear callback function, did disappear.
 * @param page_p pointer to an 'nt_page_t' page.
 * @return next state.
 */
nt_state_t nt_state_did_disappear_execute(nt_page_t * page_p)
{
    nt_load_anim_t _amin = nt_pm_loadanim_get_current_type();
    
    /*No matter what kind of animation, 
    do not show when directly hidden*/
    if (1/*_amin == LOAD_ANIM_FADE_ON*/) {

        lv_obj_add_flag(page_p->root, 
            LV_OBJ_FLAG_HIDDEN);

    }

    views[page_p->idx]->view_did_disappear();

    bool is_cached = page_p->priv.is_cached;

    if (is_cached) return NT_STATE_WILLDISAPPEAR;
    else return NT_STATE_UNLOAD;
}

/**
 * Unload callback function, unload page.
 * @param page_p pointer to an 'nt_page_t' page.
 * @return next state.
 */
nt_state_t nt_state_unload_execute(nt_page_t * page_p)
{
    if (page_p->root == NULL) return NT_STATE_IDLE;

    lv_obj_del_async(page_p->root);
    page_p->root = NULL;
    page_p->priv.is_cached = false;

    views[page_p->idx]->view_did_unload();
    return NT_STATE_IDLE;
}

/**
 * Set animation default parameters.
 * @param anim_type the type of animation.
 * @param time set the duration of the animation.
 * @param path the execution path set for the animation.
 */
void nt_pm_loadanim_set_custom_type(uint8_t anim_type, uint16_t time,
    lv_anim_path_cb_t path)
{
    if (anim_type > _LOAD_ANIM_LAST)
        anim_type = LOAD_ANIM_NONE;

    anim_state.current.type = anim_type;
    anim_state.current.time = time;
    anim_state.current.path = path;
}

/**
 * Set animation default parameters.
 * @param a pointer to an 'lv_anim_t' animation.
 * @return gets the type of animation that is 
 * currently executing.
 */
nt_load_anim_t nt_pm_loadanim_get_current_type()
{
    nt_load_anim_t _amin = LOAD_ANIM_NONE;
    _amin = (nt_load_anim_t)anim_state.current.type;

    return _amin;
}

/**
 * Set animation default parameters.
 * @param a pointer to an 'lv_anim_t' animation.
 * @return whether the properties 
 * of the page are valid.
 */
bool nt_pm_loadanim_get_current_attr(load_anim_attr_t * attr)
{
    nt_load_anim_t _amin = \
        nt_pm_loadanim_get_current_type();
    bool res = nt_anim_loadanim_get_attr(
        _amin, attr);

    return res;
}

/**
 * Create a page rotations animation.
 * @param page_p pointer to an 'nt_page_t' page, the page to animate.
 */
void nt_pm_view_rotations_anim_create(nt_page_t * page_p)
{
    load_anim_attr_t animAttr = {0};

    bool res = nt_pm_loadanim_get_current_attr(&animAttr);
    if (!res) return;

    lv_anim_t a;
    nt_pm_anim_default_init(&a);
    lv_anim_set_user_data(&a, page_p);
    lv_anim_set_var(&a, page_p->root);
    lv_anim_set_ready_cb(&a, nt_pm_view_rotations_anim_finish);
    lv_anim_set_exec_cb(&a, animAttr.setter);

    /*bool is_pushing = false;*/

    int32_t start = 0;

    if (animAttr.getter != NULL) {
        start = animAttr.getter(page_p->root);
    }

    if (anim_state.is_pushing) {
        if (page_p->priv.anim.is_enter) {
            lv_anim_set_values(
                &a,
                animAttr.push.enter.start,
                animAttr.push.enter.end
            );
        } else {
            /*Exit anim*/
            lv_anim_set_values(
                &a,
                start,
                animAttr.push.exit.end
            );
        }
    } else {
        if (page_p->priv.anim.is_enter) {
            lv_anim_set_values(
                &a,
                animAttr.pop.enter.start,
                animAttr.pop.enter.end
            );
        } else {
            /*Exit anim*/
            lv_anim_set_values(
                &a,
                start,
                animAttr.pop.exit.end
            );
        }
    }

    lv_anim_start(&a);
    page_p->priv.anim.is_busy = true;
}

/**
 * Set animation default parameters.
 * @param a pointer to an 'lv_anim_t' animation.
 */
void nt_pm_anim_default_init(lv_anim_t * a)
{
    lv_anim_init(a);

    lv_anim_path_cb_t path = lv_anim_path_ease_out;

    nt_load_anim_t _amin = \
        nt_pm_loadanim_get_current_type();

    uint32_t time = (
        _amin == LOAD_ANIM_NONE
    ) ? 0 : anim_state.current.time;

    lv_anim_set_time(a, time);
    lv_anim_set_path_cb(a, 
        anim_state.current.path);
}

/**
 * Check if the page switching animation is being executed.
 * @return true if it is executing.
 */
bool switch_anim_state_end()
{
    if (anim_state.is_switch_req || 
        anim_state.is_busy) return false;
    return true;
}

/**
 * Page switching request check.
 * @return true if all pages are executed.
 */
bool switch_req_check()
{
    bool last_node_busy = false;
    bool node_busy = false;
    bool ret = false;

    last_node_busy = pages[1].priv.anim.is_busy;
    node_busy = pages[0].priv.anim.is_busy;

    if (!node_busy && !last_node_busy) {
        /*Page switch was all finished*/
        anim_state.is_switch_req = false;
        ret = true;
    } else {
        if (node_busy) {
            /*Current page is busy*/
        } else {
            /*Prev page is busy*/
        }
    }

    return ret;
}

/**
 * Update current animation properties, apply page custom animation
 * @param page_p pointer to an 'nt_page_t' page, the page to animate.
 */
void switch_anim_update(nt_page_t * page_p)
{
    nt_load_anim_t _anim = page_p->priv.anim.attr.type;

    if (_anim == LOAD_ANIM_GLOBAL)
        anim_state.current = \
            anim_state.global;
    else {
        if (_anim > _LOAD_ANIM_LAST)
            page_p->priv.anim.attr = \
                anim_state.global;
        else {}
        anim_state.current = \
            page_p->priv.anim.attr;
    }
}

/**
 * Page rotations animation execution end callback.
 * @param a pointer to an 'lv_anim_t' animation.
 */
void nt_pm_view_rotations_anim_finish(lv_anim_t * a)
{
    nt_page_t * page_p = (nt_page_t *)lv_anim_get_user_data(a);

    /*The state of the page needs to be updated 
    once the animation of the page ends*/
    nt_page_state_update(page_p);

    page_p->priv.anim.is_busy = false;
    bool is_finished = switch_req_check();
    if (is_finished) {}
}

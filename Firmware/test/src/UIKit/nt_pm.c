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

    if(res != NT_RES_OK || anim_state.is_busy)
        return NT_RES_INV;

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

    if (pages[1].root != NULL) pages[1].is_enter = false;
    pages[0].is_enter = true;

    /*Update status information for new and old pages*/
    nt_page_state_update(&pages[1]);
    nt_page_state_update(&pages[0]);

    bool ispushing = true;

    if (ispushing) {
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
        nt_page_state_update(page_p);
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
        nt_page_state_update(page_p);
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
    lv_obj_t * root_obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(root_obj, 320, 240);
    lv_obj_clear_flag(root_obj, LV_OBJ_FLAG_SCROLLABLE);
    page_p->root = root_obj;
    views[page_p->idx]->load_view(page_p->root);
    views[page_p->idx]->view_did_load();
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
    views[page_p->idx]->view_did_disappear();

    bool load_anim_fade_on = false;

    if (load_anim_fade_on)
        lv_obj_add_flag(page_p->root, LV_OBJ_FLAG_HIDDEN);

    bool is_cached = true;

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
    lv_obj_del_async(page_p->root);
    page_p->root = NULL;

    views[page_p->idx]->view_did_unload();
    return NT_STATE_IDLE;
}

/**
 * Create a page rotations animation.
 * @param page_p pointer to an 'nt_page_t' page, the page to animate.
 */
void nt_pm_view_rotations_anim_create(nt_page_t * page_p)
{
    lv_anim_t a;
    nt_pm_anim_default_init(&a);
    lv_anim_set_user_data(&a, page_p);
    lv_anim_set_var(&a, page_p->root);
    lv_anim_set_ready_cb(&a, nt_pm_view_rotations_anim_finish);
    lv_anim_set_exec_cb(&a, lv_obj_set_y);

    bool ispushing = false;

    if (ispushing) {
        if (page_p->is_enter) {
            lv_anim_set_values(
                &a,
                240,
                0
            );
        } else {
            lv_anim_set_values(
                &a,
                0,
                -240
            );
        }
    } else {
        if (page_p->is_enter) {
            lv_anim_set_values(
                &a,
                -240,
                0
            );
        } else {
            lv_anim_set_values(
                &a,
                0,
                240
            );
        }
    }

    lv_anim_start(&a);
    anim_state.is_busy = true;
}

/**
 * Set animation default parameters.
 * @param a pointer to an 'lv_anim_t' animation.
 */
void nt_pm_anim_default_init(lv_anim_t * a)
{
    lv_anim_init(a);

    lv_anim_path_cb_t path = lv_anim_path_ease_out;

    uint32_t time = /*600*/200;
    lv_anim_set_time(a, time);
    lv_anim_set_path_cb(a, path);
}

/**
 * Page rotations animation execution end callback.
 * @param a pointer to an 'lv_anim_t' animation.
 */
void nt_pm_view_rotations_anim_finish(lv_anim_t * a)
{
    nt_page_t * page_p = (nt_page_t *)lv_anim_get_user_data(a);
    anim_state.is_busy = false;
}

/**
 * @file nt_act.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "nt_act.h"

/**********************
 *  STATIC VARIABLES
 **********************/

static const uint16_t 
active_symbol_width[_NT_ACTIVE_LAST] = {34, 20, 16, 16, 24};

const nt_active_desc_t * register_desc[8] = {0};
uint16_t register_cnt = 0;

static const nt_active_desc_t 
act_bat = {
    .act_id = NT_ACTIVE_BATTERY,
    .act_name = "battery",
    .act_pri = 10,
};

static const nt_active_desc_t 
act_time = {
    .act_id = NT_ACTIVE_TIME,
    .act_name = "time",
    .act_pri = 1,
};

static const nt_active_desc_t 
act_sound = {
    .act_id = NT_ACTIVE_SOUND,
    .act_name = "sound",
    .act_pri = 5,
};

static const nt_active_desc_t 
act_timer = {
    .act_id = NT_ACTIVE_TIMER,
    .act_name = "timer",
    .act_pri = 6,
};

static const nt_active_desc_t 
act_usb = {
    .act_id = NT_ACTIVE_USB,
    .act_name = "usb",
    .act_pri = 9,
};

/**********************
 * STATIC PROTOTYPES
 **********************/

static void nt_active_area_compute();
static void nt_active_area_update();
static void nt_active_symbol_update(uint16_t sym_id);
static void nt_active_symbol_reset();
static void nt_active_anim_ready(lv_anim_t * a);
static void nt_active_anim_create();
static void nt_active_set_size(void * data, int32_t value);

/**********************
 * GLOBAL FUNCTIONS
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
    const nt_active_desc_t * desc_p)
{
    uint16_t size = \
        NT_ARR_SIZE(register_desc);
    if (register_cnt > size - 1) 
        return NT_RES_INV;
    register_desc[register_cnt] = desc_p;
    register_cnt++;

    return NT_RES_OK;
}

/**
 * Gets the number of registered activity descriptors.
 * @return number of registered descriptors.
 */
uint16_t nt_active_get_register_cnt()
{
    return register_cnt;
}

/**
 * Gets the index of the active from the active name string.
 * @param name pointer to active name.
 * @param idx gets the result of the name.
 * @return convert result.
 */
uint8_t nt_active_name_get_id(uint8_t * name, 
    uint16_t * idx)
{
    const uint8_t * _name = NULL;
    uint16_t size = 0;
    size = NT_ARR_SIZE(register_desc);
    for (uint16_t i = 0; i < size; i++) {
        _name = register_desc[i]->act_name;
        if (!strcmp(_name, name)) {
            *idx = i;
            return NT_RES_OK;
        }
    }
    return NT_RES_INV;
}

/**
 * Gets the display size of the active symbol that can be used for 
 * subsequent dynamic display coordinate calculations.
 * @param act_sym active symbol name.
 * @return symbol width.
 */
uint16_t nt_active_get_symbol_size(
    nt_active_symbol_t act_sym)
{
    uint16_t width = 0;

    if (act_sym > NT_ACTIVE_BATTERY) return 0;
    if (act_sym < NT_ACTIVE_TIME) return 0;

    width = active_symbol_width[act_sym];

    return width;
}

nt_active_t actives[5] = {0};
uint16_t active_cnt = 0;

/**
 * Gets the index of the active from the active name string.
 * @param name pointer to active name.
 * @param idx gets the result of the name.
 * @return convert result.
 */
uint8_t nt_active_name_get_act_id(uint8_t * name, 
    uint16_t * idx)
{
    const uint8_t * _name = NULL;
    uint16_t size = NT_ARR_SIZE(actives);
    for (uint8_t i = 0; i < size; i++) {
        _name = actives[i].name;
        if (!strcmp(_name, name)) {
            *idx = i;
            return NT_RES_OK;
        }
    }
    return NT_RES_INV;
}

/**
 * Gets the number of activities that have been cached in the active cache.
 * @return number of cached active.
 */
uint16_t nt_active_get_active_cnt()
{
    return active_cnt;
}

uint8_t need_update = false;

/**
 * Start the active with the name, start new active, update the active cached.
 * @param name active name.
 * @return start result.
 */
nt_res_t nt_start_active(uint8_t * name)
{
    uint16_t act_idx = 0;
    uint16_t _act_idx;
    uint16_t size = 0;

    size = NT_ARR_SIZE(actives);

    /*Query the validity of the activity name*/
    nt_res_t res = nt_active_name_get_id(name, &act_idx);
    if(active_cnt > size - 1) return NT_RES_INV;
    if(res != NT_RES_OK) return NT_RES_INV;

    /*Call the active buffer*/
    res = nt_active_name_get_act_id(name, &_act_idx);
    if(res == NT_RES_OK) return NT_RES_OK;

    /*info("nt_start_active");*/

    strncpy(actives[active_cnt].name, name, 8);
    actives[active_cnt].idx = act_idx;
    actives[active_cnt].anim = false;
    actives[active_cnt].isact = true;
    active_cnt++;

    need_update = true;

    return NT_RES_OK;
}

/**
 * Remove the active with the name, remove a active, update the active cached.
 * @param name active name.
 * @return start result.
 */
nt_res_t nt_remove_active(uint8_t * name)
{
    uint16_t act_idx = 0;
    uint16_t _act_idx;
    uint16_t size = 0;

    size = NT_ARR_SIZE(actives);

    /*Query the validity of the activity name*/
    nt_res_t res = nt_active_name_get_id(name, &act_idx);
    if(res != NT_RES_OK) return NT_RES_OK;

    /*Call the active buffer*/
    res = nt_active_name_get_act_id(name, &_act_idx);
    if(res != NT_RES_OK) return NT_RES_OK;

    /*info("nt_start_active");*/

    memset(&actives[_act_idx], '\0', 
        sizeof(nt_active_t));
    active_cnt--;

    nt_active_clean_node();

    need_update = true;

    return NT_RES_OK;
}

/**
 * Clears the closed activity from the activity cache.
 */
void nt_active_clean_node()
{
    uint16_t act_size = sizeof(nt_active_t);
    uint16_t len = NT_ARR_SIZE(actives);

    nt_active_t * active_p = actives;
    nt_active_t t_act = {0};

    for (uint16_t i = 0; i < len; i++) {
        for (uint16_t j = 0; 
            j < len - 1; j++) {

            if (active_p[j].name[0] < 
                active_p[j + 1].name[0]) {
                memcpy(
                    &t_act, 
                    &active_p[j], 
                    act_size);
                memcpy(
                    &active_p[j], 
                    &active_p[j + 1], 
                    act_size);
                memcpy(
                    &active_p[j + 1], 
                    &t_act, 
                    act_size);
            }
        }
    }
}

/**
 * The active node objects that are already active are prioritized.
 */
void nt_active_filte_act_node()
{
    uint16_t len = nt_active_get_active_cnt();
    uint16_t act_size = sizeof(nt_active_t);

    nt_active_t * active_p = actives;
    nt_active_t t_act = {0};

    uint16_t  idx = 0;
    uint16_t _idx = 0;

    uint32_t  pri = 0;
    uint32_t _pri = 0;

    for (uint16_t i = 0; i < len; i++) {
        for (uint16_t j = 0; 
            j < len - 1; j++) {

            idx  = active_p[j + 0].idx;
            _idx = active_p[j + 1].idx;

            pri  = register_desc[
                idx]->act_pri;
            _pri = register_desc[
                _idx]->act_pri;

            if (pri < _pri) {
                memcpy(
                    &t_act, 
                    &active_p[j], 
                    act_size);
                memcpy(
                    &active_p[j], 
                    &active_p[j + 1], 
                    act_size);
                memcpy(
                    &active_p[j + 1], 
                    &t_act, 
                    act_size);
            }
        }
    }
}

nt_active_t filted_active[5] = {0};
uint16_t filted_act_cnt = 0;
uint16_t filted_max = 5;
uint8_t active_mod = 0;

/**
 * Gets the number of activities that have been filted 
 * in the active cache.
 * @return number of filted active.
 */
uint16_t nt_active_get_filted_cnt()
{
    return filted_act_cnt;
}

/**
 * Extract the three highest priority activities from each of 
 * the activity caches and add them to the filter list.
 */
void nt_active_filte_node()
{
    uint16_t act_size = sizeof(nt_active_t);
    nt_active_t * active_p = actives;
    const uint8_t * name = NULL;
    bool isact = 0;
    uint16_t idx = 0;
    uint32_t pri = 0;

    for (uint16_t i = 0; i < filted_max; i++) {
        idx = active_p[i].idx;
        isact = active_p[i].isact;
        name = active_p[i].name;
        
        /*info("idx:%d", idx);*/

        pri = register_desc[
            idx]->act_pri;

        if (name[0] == '\0') continue;
        if (!isact) continue;

        if ((active_mod == 0) && 
            (filted_act_cnt >= 2) && 
            (pri == 1)
        ) continue;

        memcpy(
            &filted_active[
                filted_act_cnt], 
            &active_p[i], 
            act_size);

        /*active_p[i].isact = false;*/
        filted_act_cnt++;
    }
}

nt_active_area_t area = {0};

/**
 * Update active display drive coordinates 
 * and dimensions.
 */
static void nt_active_area_compute()
{
    uint16_t act_id = 0;
    uint32_t width = 0;

    /*info("filted:%d", filted_act_cnt);*/

    for (uint16_t i = 0; i < filted_act_cnt; i++) {
        act_id = register_desc[
            filted_active[i].idx]->act_id;
        width = nt_active_get_symbol_size(act_id);
        area.w += width;
        nt_active_symbol_update(act_id);
    }
}

/**
 * Update the position and size of the active symbol.
 * Note that the coordinates do not take effect 
 * immediately after they are set.
 */
static void nt_active_area_update()
{
    area.w += SYM_GAP_DEF;
    area.x = SYM_END_DEF - area.w;

    lv_obj_set_pos(
        statbar_view.cont, 
        area.x, 
        area.y
    );

    lv_obj_set_size(
        statbar_view.cont, 
        area.w, 
        20
    );
}

/**
 * The status of the associated symbol is updated based on 
 * the symbol ID of the bound by the activated activity.
 * @param sym_id active symbol ID.
 */
static void nt_active_symbol_update(uint16_t sym_id)
{
    switch (sym_id) {
    case NT_ACTIVE_TIME:
        nt_statbar_time_hide(false);
        break;
    case NT_ACTIVE_USB:
        nt_statbar_usb_hide(false);
        break;
    case NT_ACTIVE_TIMER:
        nt_statbar_timer_hide(false);
        break;
    case NT_ACTIVE_SOUND:
        nt_statbar_sound_hide(false);
        break;
    case NT_ACTIVE_BATTERY:
        nt_statbar_bat_hide(false);
        break;
    }
}

/**
 * Reset the status of the active symbol.
 */
static void nt_active_symbol_reset()
{
    nt_statbar_time_hide(true);
    nt_statbar_usb_hide(true);
    nt_statbar_timer_hide(true);
    nt_statbar_sound_hide(true);
    nt_statbar_bat_hide(true);
}

/**
 * Reset the status of the active symbol, update the status of the active symbol, 
 * perform recommendations, calculate the position of the active symbol, 
 * update the active bar and so on.
 */
void nt_active_update()
{
    if (!need_update) return;

    nt_active_symbol_reset();

    nt_active_filte_act_node();
    nt_active_filte_node();

    nt_active_area_compute();
    nt_active_area_update();

    nt_active_anim_create();

    filted_act_cnt = 0;
    /*active_cnt = 0;*/
    area.w = 0;
    area.x = 0;

    /*memset(actives, '\0', sizeof(nt_active_t) * 5);*/
    /*memset(filted_active, '\0', sizeof(nt_active_t) * 3);*/

    /*info("Active update");*/

    need_update = false;
}

/**
 * Set the activity manager to run in 
 * select or recommended mode.
 * @param mod active running mode.
 */
void nt_active_set_mode(uint8_t mod)
{
    if (!mod) {
        filted_max = 3;
        area.y = 1;
    } else {
        filted_max = 5;
        area.y = 2;
    }

    active_mod = mod;
    need_update = true;
}

/**
 * Gets the current state of the specified activity 
 * by the activity name.
 * @param name active name.
 */
bool nt_active_get_state(uint8_t * name)
{
    uint16_t _act_idx;

    /*Call the active buffer*/
    nt_res_t res = nt_active_name_get_act_id(name, &_act_idx);
    if(res != NT_RES_OK) return false;
    return true;
}

int16_t act_ori_x = 0;
int16_t act_ori_width = 0;

/**
 * The animation ends and the change takes effect,
 * To improve performance, LVGL does not immediately 
 * recalculate coordinate changes only refreshes 
 * their location, size, and layout before 
 * redrawing the screen.
 * @param a active anim.
 */
static void nt_active_anim_ready(
    lv_anim_t * a)
{
    lv_obj_update_layout(
            statbar_view.cont);
}

/**
 * Create a transition animation for event changes and 
 * event symbol size and coordinates updates to flow.
 */
static void nt_active_anim_create()
{
    lv_anim_t a;
    lv_anim_path_cb_t path;
    uint32_t time = 300;

    if (1) path = lv_anim_path_ease_out;
    else path = lv_anim_path_overshoot;

    lv_anim_init(&a);

    lv_anim_set_time(&a, time);
    lv_anim_set_path_cb(&a, path);

    lv_anim_set_var(&a, 
        statbar_view.cont);
    lv_anim_set_ready_cb(&a, 
        nt_active_anim_ready);

    if (1) lv_anim_set_exec_cb(&a, lv_obj_set_x);
    else lv_anim_set_exec_cb(&a, nt_active_set_size);


    lv_coord_t ori_pos = \
        lv_obj_get_x(statbar_view.cont);

    lv_coord_t ori_width = \
        lv_obj_get_width(
            statbar_view.cont);

    act_ori_x = ori_pos;
    act_ori_width = ori_width;

    lv_anim_set_values(
        &a,
        ori_pos,
        area.x
    );

    if (area.x != ori_pos) {
        lv_anim_start(&a);
    }
}

/**
 * Perform animation operations to achieve 
 * smooth size and coordinate change process.
 * Note that the coordinates do not take effect 
 * immediately after they are set.
 * @param value changing value.
 */
static void nt_active_set_size(void * data, 
    int32_t value)
{
    int16_t x_ofs = act_ori_x - value;

    lv_obj_set_x(
        statbar_view.cont, 
        value
    );

    lv_obj_set_width(
        statbar_view.cont, 
        act_ori_width + x_ofs
    );
}

/**
 * Registers the defined event object with 
 * the recommendation engine.
 */
void nt_active_desc_init()
{
    _nt_active_desc_register(&act_bat);
    _nt_active_desc_register(&act_time);
    _nt_active_desc_register(&act_sound);
    _nt_active_desc_register(&act_timer);
    _nt_active_desc_register(&act_usb);
}

/**
 * @file nt_rm.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "nt_rm.h"


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Construct a default resource as an alternate*/
static const lv_font_t res_def = {0};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Searches the list to which the resource Explorer belongs 
 * for the specified resource.
 * @param rm Points to a resource explorer.
 * @param id resource name.
 * @param desc_p pointer to resource descriptor searched for.
 * @return true if the search is successful.
 */
nt_res_t nt_rm_find_form_ll(nt_rm_t * rm, 
    const int8_t * id, nt_res_desc_t * desc_p)
{
    uint16_t size = NT_ARR_SIZE(rm->desc_ll);
    for (uint16_t i = 0; i < size; i++) {
        if (!strcmp(rm->desc_ll[i].id, id)) {
            *desc_p = rm->desc_ll[i];
            return NT_RES_OK;
        }
    }
    return NT_RES_INV;
}

/**
 * Searches the list to which the resource Explorer belongs 
 * for the specified resource.
 * @param rm Points to a resource explorer.
 * @param id resource name.
 * @param idx pointer to resource index searched for.
 * @return true if the search is successful.
 */
nt_res_t nt_rm_find_idx_form_ll(nt_rm_t * rm, 
    const int8_t * id, uint16_t * idx)
{
    uint16_t size = NT_ARR_SIZE(rm->desc_ll);
    for (uint16_t i = 0; i < size; i++) {
        if (!strcmp(rm->desc_ll[i].id, id)) {
            *idx = i;
            return NT_RES_OK;
        }
    }
    return NT_RES_INV;
}

/**
 * Organize the resources in the list in order.
 * @param rm Points to a resource explorer.
 * @param idx The starting position of the resources to be sorted.
 * @return Resources Order result.
 */
uint8_t nt_rm_resource_forward(nt_rm_t * rm, uint16_t * idx)
{
    uint16_t size = NT_ARR_SIZE(rm->desc_ll);
    if (*idx > (size - 1)) return NT_RES_INV;

    memset(&rm->desc_ll[*idx], 
        0, sizeof(nt_res_desc_t)
    );

    for (uint16_t i = *idx; i < size; i++)
        rm->desc_ll[i] = rm->desc_ll[i + 1];

    return NT_RES_OK;
}

/**
 * Add resources to the resource pool.
 * @param rm Points to a resource explorer.
 * @param id resource name.
 * @param ptr pointer to the resource.
 * @return true if the addition is successful.
 */
nt_res_t nt_rm_resource_register(nt_rm_t * rm, 
    const int8_t * id, void * ptr)
{
    nt_res_desc_t desc = {0};

    nt_res_t res = \
        nt_rm_find_form_ll(rm, id, &desc);

    if (res != NT_RES_INV) {
        info("resource: %s registered", id);
        return NT_RES_INV;
    }

    uint16_t size = NT_ARR_SIZE(rm->desc_ll);

    rm->wrong = true;

    if (rm->cnt > size - 1) return NT_RES_INV;

    desc.id = id;
    desc.ptr = ptr;
    
    rm->desc_ll[rm->cnt] = desc;
    rm->cnt++;
    rm->wrong = false;

    return NT_RES_OK;
}

/**
 * Removes a specified resource from a specified resource Explorer.
 * @param rm Points to a resource explorer.
 * @param id resource name.
 * @return true if the addition is successful.
 */
nt_res_t nt_rm_resource_remove(nt_rm_t * rm, 
    const int8_t * id)
{
    nt_res_desc_t desc = {0};
    uint16_t idx = 0;

    nt_res_t res = \
        nt_rm_find_form_ll(rm, id, &desc);

    if (res != NT_RES_OK) {
        info("resource: %s not register", id);
        return NT_RES_INV;
    }

    res = nt_rm_find_idx_form_ll(rm, id, &idx);

    if (res != NT_RES_OK) {
        info("resource: %s not register", id);
        return NT_RES_INV;
    }

    uint16_t size = NT_ARR_SIZE(rm->desc_ll);

    if (idx > size - 1) return NT_RES_INV;

    res = nt_rm_resource_forward(rm, &idx);

    if (res) rm->cnt--;

    return NT_RES_OK;
}

/**
 * Gets resources from the specified resources Explorer.
 * @param rm points to a resource explorer.
 * @param id resource name.
 * @return if the acquisition is successful, return the 
 * address of the resource, otherwise return 
 * the default resource
 */
void * nt_rm_get_resource(nt_rm_t * rm, const int8_t * id)
{
    nt_res_desc_t desc = {0};

    nt_res_t res = \
        nt_rm_find_form_ll(rm, id, &desc);

    if (res != NT_RES_OK) return rm->defptr;

    return desc.ptr;
}

/**
 * Bind the resource explorer to a default resource as an alternate.
 * @param rm Points to a resource explorer.
 * @param ptr pointer to the default resource.
 */
void nt_rm_set_default(nt_rm_t * rm, void * ptr)
{
    if (ptr != NULL) rm->defptr = ptr;
    else rm->defptr = (void *)&res_def;
}

/**
 * Gets the number of registered resources.
 * @param rm Points to a resource explorer.
 * @return number of resources is registered.
 */
uint16_t nt_rm_get_resource_cnt(nt_rm_t * rm)
{
    return rm->cnt;
}

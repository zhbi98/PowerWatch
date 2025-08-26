/**
 * @file nt_rm.h
 *
 */

#ifndef __NT_RM_H__
#define __NT_RM_H__

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"
#include "nt_pm.h"
#include <stdint.h>
#include <string.h>
#include "log.h"

/*********************
 *      DEFINES
 *********************/

#ifndef NT_RESRC_MAX
#define NT_RESRC_MAX 12U
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Describes the information contained in a resource, 
 * such as the resource name.
 */
typedef struct {
    void * ptr; /**< Points to the resource*/
    const uint8_t * id; /**< Resource name*/
} nt_res_desc_t;

/**
 * To construct a File Explorer object.
 */
typedef struct {
	void * defptr; /**< Points to the default resource*/
	nt_res_desc_t desc_ll[NT_RESRC_MAX];
	uint16_t cnt;
	bool wrong; /**< Whether an exception occurs*/
} nt_rm_t;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

nt_res_t nt_rm_find_form_ll(nt_rm_t * rm, 
    const int8_t * id, nt_res_desc_t * desc_p);
nt_res_t nt_rm_resource_register(nt_rm_t * rm, 
    const int8_t * id, void * ptr);
nt_res_t nt_rm_resource_remove(nt_rm_t * rm, 
    const int8_t * id);
void * nt_rm_get_resource(nt_rm_t * rm, 
	const int8_t * id);
void nt_rm_set_default(nt_rm_t * rm, void * ptr);
uint16_t nt_rm_get_resource_cnt(nt_rm_t * rm);

#endif /*__NT_RM_H__*/

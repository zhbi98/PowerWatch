/**
 * @file resource.h
 *
 */

#ifndef __RESOURCE_H__
#define __RESOURCE_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>
#include "nt_rm.h"
#include "lvgl.h"

/*********************
 *      DEFINES
 *********************/

#ifdef  NT_RESRC_MAX
#undef  NT_RESRC_MAX
#define NT_RESRC_MAX 12U
#endif

/**********************
 *      TYPEDEFS
 **********************/

extern nt_rm_t rm_font;
extern nt_rm_t rm_sym;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void _nt_resource_init();
lv_font_t * reqfont(const int8_t * id);
lv_font_t * reqsym(const int8_t * id);

#endif /*__RESOURCE_H__*/

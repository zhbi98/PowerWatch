/**
 * @file dialplate.h
 *
 */

#ifndef __DIALPLATE_H__
#define __DIALPLATE_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>
#include "lvgl.h"
#include "dialplateview.h"
#include "elec.h"
#include "average.h"
#include "strifica.h"
#include "nt_pm.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
	unsigned char cont1_mode;
	unsigned char cont2_mode;
} DisplayMode;

extern DisplayMode displayMode;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern const nt_view_t dialplateview;

#endif

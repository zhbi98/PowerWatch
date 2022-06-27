
#ifndef __MEAS_H__
#define __MEAS_H__

#include "lvgl.h"
#include "MeasView.h"
#include "elec.h"
#include "average.h"
#include "curation.h"

typedef struct {
	unsigned char cont1_mode;
	unsigned char cont2_mode;
} DisplayMode;

extern DisplayMode displayMode;

extern void measLoadView(lv_obj_t * root);
extern void measLoadGroup();
extern void measAttachEvent(lv_obj_t * obj);
extern void measUpdate();
extern void measOnEvent(lv_event_t * event);

#endif

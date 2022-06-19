
#ifndef __MEAS_H__
#define __MEAS_H__

#include "lvgl.h"
#include "ina226.h"
#include "MeasView.h"
#include "data_pool.h"
#include "elec.h"

typedef struct {
    float sum;
    float avg;
    unsigned char type;
} Average;

extern Average average;
extern struct data_pool_t avg_pool;
extern void electricalEnergy();
extern void electricalAverage();

typedef struct {
	unsigned char mode;
} DisplayMode;

extern DisplayMode displayMode;

extern void measLoadView(lv_obj_t * root);
extern void measLoadGroup();
extern void measAttachEvent(lv_obj_t * obj);
extern void measUpdate();
extern void measOnEvent(lv_event_t * event);

#endif

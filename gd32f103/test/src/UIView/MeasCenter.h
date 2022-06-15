
#ifndef __MEAS_CENTER_H__
#define __MEAS_CENTER_H__

#include "lvgl.h"
#include "ina226.h"
#include "MeasCenterView.h"
#include "data_pool.h"

#define ENERGY_TIME (0.1f / 3600)

typedef struct {
    float mAh;
    float mWh;
} Energy;

typedef struct {
    float sum;
    float avg;
} Average;

extern Energy energy;
extern Average average;
extern struct data_pool_t data_pool;
extern void electricalEnergy();

extern void measCenterLoadView(lv_obj_t * root);
extern void measCenterLoadGroup();
extern void measCenterAttachEvent(lv_obj_t * obj);
extern void measCenterUpdate();
extern void measCenterOnEvent(lv_event_t * event);

#endif

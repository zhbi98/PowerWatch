
#ifndef __MEAS_CENTER_H__
#define __MEAS_CENTER_H__

#include "lvgl.h"
#include "ina226.h"
#include "MeasCenterView.h"

extern float avgsum;
extern float avgv;
extern char  avgt;
extern float mAh;
extern float mWh;
extern char  t;

extern void measCenterLoadView(lv_obj_t * root);
extern void measCenterLoadGroup();
extern void measCenterAttachEvent(lv_obj_t * obj);
extern void measCenterUpdate();
extern void measCenterOnEvent(lv_event_t * event);

#endif

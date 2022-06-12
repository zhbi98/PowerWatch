
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

extern lv_timer_t * updataTimer;

extern void measCenterUpdate();
extern void timerUpdateCreate();

#endif

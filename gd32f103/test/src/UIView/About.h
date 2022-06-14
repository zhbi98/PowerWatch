
#ifndef __ABOUT_H__
#define __ABOUT_H__

#include "lvgl.h"
#include "AboutView.h"

extern void aboutLoadView(lv_obj_t * root);
extern void aboutLoadGroup();
extern void aboutAttachEvent(lv_obj_t * obj);
extern void aboutViewUpdate();
extern void aboutOnEvent(lv_event_t * event);

#endif


#ifndef __NORMALMODEVIEW_H__
#define __NORMALMODEVIEW_H__

#include "lvgl.h"

typedef struct {
    lv_obj_t * cont;
    lv_obj_t * outputLabel;
} UIOutputLabel;

typedef struct {
    lv_obj_t * cont;
    lv_obj_t * powerLabel;
    lv_obj_t * voltageLabel;
    lv_obj_t * currentLabel;
} UIMeasureGroup;

typedef struct {
    lv_obj_t * cont;
    lv_obj_t * socketLabel;
} UISocketLabel;

typedef struct {
	UIOutputLabel uiOutputLabel;
	UIMeasureGroup uiMeasureGroup;
	UISocketLabel uiSocketLabel;
} UINormalMode;

extern UINormalMode uiNormalModeView;

extern void normalModeViewCreate(lv_obj_t * root);

#endif

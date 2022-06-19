
#ifndef __SHEET_H__
#define __SHEET_H__

#include <stdlib.h>
#include "SheetView.h"

extern void sheetLoadView(lv_obj_t * root);
extern void sheetLoadGroup();
extern void sheetAttachEvent(lv_obj_t * obj);
extern void sheetUpdate();
extern void sheetOnEvent(lv_event_t * event);

#endif

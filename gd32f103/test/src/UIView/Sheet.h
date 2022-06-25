
#ifndef __SHEET_H__
#define __SHEET_H__

#include <stdlib.h>
#include "cache.h"
#include "SheetView.h"

extern struct cache_buffer_t bar_cache_buf;

extern void sheetLoadView(lv_obj_t * root);
extern void sheetLoadGroup();
extern void sheetAttachEvent(lv_obj_t * obj);
extern void sheetUpdate();
extern void sheetOnEvent(lv_event_t * event);

extern void bar_cache_hanlder(float value);

#endif

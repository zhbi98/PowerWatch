
#ifndef __UIKIT_H__
#define __UIKIT_H__

#include "lvgl.h"

typedef struct {
    unsigned char pageNum;
    unsigned char * pageName;
	lv_obj_t * root;
	void (*loadView)();
} UIKitType;

#endif

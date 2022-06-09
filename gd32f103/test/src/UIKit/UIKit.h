
#ifndef __UIKIT_H__
#define __UIKIT_H__

#include "lvgl.h"

typedef void UIView(lv_obj_t *);

typedef struct {
    unsigned char pageNum;
    unsigned char * pageName;
    lv_obj_t * root;
    // void (*loadView)(lv_obj_t *);
    UIView * loadView;
} UIKitType;

#endif

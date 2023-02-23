
#ifndef __UIKIT_H__
#define __UIKIT_H__

#include "lvgl.h"

typedef void UIView(lv_obj_t *);
typedef void UIViewUpdate();
typedef void UIViewLoadGroup();

/* Page state */
typedef enum {
    PAGE_STATE_LOAD,
    PAGE_STATE_UNLOAD,
    _PAGE_STATE_LAST
} ViewState;

typedef struct {
    lv_obj_t * root;
    unsigned char pageNum;
    unsigned char * pageName;
    // void (*loadView)(lv_obj_t *);
    UIView * loadView;
    UIViewUpdate * uiViewUpdate;
    UIViewLoadGroup * uiViewGroup;
    ViewState State;
} UIKitType;

#endif

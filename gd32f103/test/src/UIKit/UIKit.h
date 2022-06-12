
#ifndef __UIKIT_H__
#define __UIKIT_H__

#include "lvgl.h"

typedef void UIView(lv_obj_t *);

/* Page state */
typedef enum {
    PAGE_STATE_IDLE,
    PAGE_STATE_LOAD,
    PAGE_STATE_WILL_APPEAR,
    PAGE_STATE_DID_APPEAR,
    PAGE_STATE_ACTIVITY,
    PAGE_STATE_WILL_DISAPPEAR,
    PAGE_STATE_DID_DISAPPEAR,
    PAGE_STATE_UNLOAD,
    _PAGE_STATE_LAST
} PageState;

typedef struct {
    unsigned char pageNum;
    unsigned char * pageName;
    lv_obj_t * root;
    // void (*loadView)(lv_obj_t *);
    UIView * loadView;
    PageState State;
} UIKitType;

#endif

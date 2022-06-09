
#include "UIViewController.h"

UIStackAddrDef uiStack;
UIVectorDef uiVector;

void viewInit(unsigned char * name, UIView * loadView)
{
    UIKitType UIView;
    UIView.pageNum = 0,
    UIView.pageName = name,
    UIView.root = NULL,
    UIView.loadView = loadView,

    vectorPush(&uiVector, UIView);
}

void viewStackPush(unsigned char * name)
{
    if (stackFindAddress(uiStack, name) == true)
        return;
    if (vectorFind(uiVector, name) == false)
        return;

    UIKitType * uiView = vectorNameGetAddress(&uiVector, name);
    stackPushAddress(&uiStack, uiView);

    lv_obj_t * root_obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(root_obj, MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_obj_clear_flag(root_obj, LV_OBJ_FLAG_SCROLLABLE);

    if (uiView->root != NULL) {
        lv_obj_remove_style_all(uiView->root);
        lv_obj_clean(uiView->root);
        // Asynchronous deletes are deleted on the next `lv_task_handler()` call.
        lv_obj_del_async(uiView->root);
        uiView->root = NULL;
    }

    uiView->root = root_obj;
    uiView->loadView(uiView->root);

    lv_obj_move_foreground(uiView->root);
}

void viewStackPop()
{
    UIKitType * top;

    if (stackEmptyAddress(&uiStack) == true)
        return;

    stackPopAddress(&uiStack, &top);
    stackTopAddress(&uiStack, &top);

    lv_obj_t * root_obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(root_obj, MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_obj_clear_flag(root_obj, LV_OBJ_FLAG_SCROLLABLE);

    if (top->root != NULL) {
        lv_obj_remove_style_all(top->root);
        lv_obj_clean(top->root);
        // Asynchronous deletes are deleted on the next `lv_task_handler()` call.
        lv_obj_del_async(top->root);
        top->root = NULL;
    }

    top->root = root_obj;
    top->loadView(top->root);

    lv_obj_move_foreground(top->root);
}

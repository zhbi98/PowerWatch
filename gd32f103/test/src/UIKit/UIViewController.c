
#include "UIViewController.h"

UIStackAddrDef uiStack;
UIVectorDef uiVector;
UIViewController viewController;

void viewInit(unsigned char * name, UIView * loadView)
{
    UIKitType UIView;
    UIView.pageNum = 0;
    UIView.pageName = name;
    UIView.root = NULL;
    UIView.loadView = loadView;

    viewController.prevPage = NULL;
    viewController.currentPage = NULL;

    // The page has been initialized
    if (vectorFindAddress(&uiVector, name) == true)
        return;

    stackInitAddress(&uiStack);
    vectorPush(&uiVector, UIView);
}

void viewStackPush(unsigned char * name)
{
    if (stackFindAddress(uiStack, name) == true)
        return;
    if (vectorFindAddress(&uiVector, name) == false)
        return;

    UIKitType * uiView = vectorNameGetAddress(&uiVector, name);
    stackPushAddress(&uiStack, uiView);

    viewSwitch(uiView, true);
}

void viewStackPop()
{
    UIKitType * top;

    if (stackEmptyAddress(&uiStack) == true)
        return;

    stackPopAddress(&uiStack, &top);
    stackTopAddress(&uiStack, &top);

    viewSwitch(top, false);
}

void viewSwitch(UIKitType * newView, unsigned char isPushActive)
{
    viewController.currentPage = newView;
    
    lv_obj_t * root_obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(root_obj, MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_obj_clear_flag(root_obj, LV_OBJ_FLAG_SCROLLABLE);

    if (viewController.currentPage->root != NULL) {
        lv_obj_remove_style_all(viewController.currentPage->root);
        lv_obj_clean(viewController.currentPage->root);
        // Asynchronous deletes are deleted on the next `lv_task_handler()` call.
        lv_obj_del_async(viewController.currentPage->root);
        viewController.currentPage->root = NULL;
    }

    viewController.currentPage->root = root_obj;
    viewController.currentPage->loadView(viewController.currentPage->root);

    /* Move the layer, move the new page to the front */
    if (isPushActive) {
        // PM_LOG_INFO("Page PUSH is detect, move Page(%s) to foreground", PageCurrent->Name);
        if (viewController.prevPage != NULL)
            lv_obj_move_foreground(viewController.prevPage->root);
        lv_obj_move_foreground(viewController.currentPage->root);
    } else {
        // PM_LOG_INFO("Page POP is detect, move Page(%s) to foreground", GetPagePrevName());
        lv_obj_move_foreground(viewController.currentPage->root);
        if (viewController.prevPage != NULL)
            lv_obj_move_foreground(viewController.prevPage->root);
    }
}

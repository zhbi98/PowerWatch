
#include "UIViewController.h"

UIStackAddrDef uiStack;
UIVectorDef uiVector;
UIViewController viewController;

void viewInit(unsigned char * name, UIView * loadView)
{
    // The page has been initialized
    if (vectorFindAddress(&uiVector, name) == true)
        return;

    UIKitType UIView;
    UIView.root     = NULL;
    UIView.pageNum  = 0;
    UIView.pageName = name;
    UIView.loadView = loadView;
    UIView.State    = PAGE_STATE_UNLOAD;

    viewController.oldPage = NULL;

    stackInitAddress(&uiStack);
    vectorPush(&uiVector, UIView);
}

void viewStackPush(unsigned char * name)
{
    // // Undefined's page
    // if (vectorFindAddress(&uiVector, name) == false)
    //     return;
    // // The page has been pushed to the stack
    // if (stackFindAddress(uiStack, name) == true)
    //     return;

    UIKitType * uiView = vectorNameGetAddress(&uiVector, name);
    stackPushAddress(&uiStack, uiView);

    viewSwitch(uiView, true);
}

void viewStackPop()
{
    // UIKitType * uiView;

    // // UIView stack empty
    // if (stackEmptyAddress(&uiStack) == true)
    //     return;

    // stackPopAddress(&uiStack, &uiView);
    // viewController.oldPage = uiView;
    // stackTopAddress(&uiStack, &uiView);

    // viewSwitch(uiView, false);
}

void viewSwitch(UIKitType * uiView, unsigned char isPushActive)
{
    lv_obj_t * root_obj = NULL;

    if (uiView->State == PAGE_STATE_UNLOAD) {
        root_obj = lv_obj_create(lv_scr_act());
        // lv_obj_set_size(root_obj, MY_DISP_HOR_RES, MY_DISP_VER_RES);
        // lv_obj_clear_flag(root_obj, LV_OBJ_FLAG_SCROLLABLE);
        uiView->State = PAGE_STATE_LOAD;
        uiView->root = root_obj;
        uiView->loadView(uiView->root);
        lv_obj_move_foreground(uiView->root);
    } else if (uiView->State == PAGE_STATE_LOAD) {
        lv_obj_move_foreground(uiView->root);

        // lv_obj_remove_style_all(viewController.oldPage->root);
        // lv_obj_clean(viewController.oldPage->root);
        // lv_obj_del_async(viewController.oldPage->root);
        // viewController.oldPage->root = NULL;
        // viewController.oldPage->State = PAGE_STATE_UNLOAD;
    }

    // Free page elements to prevent memory leaks
    // if (uiView->root != NULL) {
    //     lv_obj_remove_style_all(uiView->root);
    //     lv_obj_clean(uiView->root);
    //     // Asynchronous deletes are deleted on the next `lv_task_handler()` call.
    //     lv_obj_del_async(uiView->root);
    //     uiView->root = NULL;
    // }
}

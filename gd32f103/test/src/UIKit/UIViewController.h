
#ifndef __UIVIEWCONTROLLER_H__
#define __UIVIEWCONTROLLER_H__

#include "lvgl.h"
#include "UIKit.h"
#include "Utils.h"
#include "UIStack.h"
#include "UIVector.h"

typedef struct {
	UIKitType * currentPage;
} UIViewController;

// uiStack and uiVector can be defined in UIViewController
extern UIStackAddrDef uiStack;
extern UIVectorDef uiVector;
extern UIViewController viewController;

extern void UIViewInit(unsigned char * name, UIView * loadView, UIViewUpdate * update, UIViewLoadGroup * loadGroup);
extern void UIViewLoad(unsigned char * name);
extern void UIViewSwitch(UIKitType * uiView, unsigned char isPushActive);

#endif

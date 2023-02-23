
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

extern void uiViewInit(unsigned char * name, UIView * loadView, UIViewUpdate * update, UIViewLoadGroup * loadGroup);
extern void uiViewLoad(unsigned char * name);
extern void uiViewSwitch(UIKitType * uiView, unsigned char isPushActive);

#endif

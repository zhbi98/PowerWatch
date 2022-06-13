
#ifndef __UIVIEWCONTROLLER_H__
#define __UIVIEWCONTROLLER_H__

#include "lvgl.h"
#include "UIKit.h"
#include "Utils.h"
#include "UIStack.h"
#include "UIVector.h"

typedef struct {
	UIKitType * oldPage;
} UIViewController;

// uiStack and uiVector can be defined in UIViewController
extern UIStackAddrDef uiStack;
extern UIVectorDef uiVector;
extern UIViewController viewController;

extern void viewInit(unsigned char * name, UIView * loadView);
extern void viewStackPush(unsigned char * name);
extern void viewStackPop();
extern void viewSwitch(UIKitType * uiView, unsigned char isPushActive);

#endif

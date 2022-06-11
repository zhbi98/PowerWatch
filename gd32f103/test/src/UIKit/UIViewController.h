
#ifndef __UIVIEWCONTROLLER_H__
#define __UIVIEWCONTROLLER_H__

#include "lvgl.h"
#include "UIKit.h"
#include "Utils.h"
#include "UIStack.h"
#include "UIVector.h"

typedef struct {
	UIKitType prevPage;
	UIKitType currentPage;
} UIViewController;

// uiStack 和 uiVector 可以定义到 UIViewController 中
extern UIStackAddrDef uiStack;
extern UIVectorDef uiVector;
extern UIViewController viewController;

extern void viewInit(unsigned char * name, UIView * loadView);
extern void viewStackPush(unsigned char * name);
extern void viewStackPop();

#endif

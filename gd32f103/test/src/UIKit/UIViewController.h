
#ifndef __UIVIEWCONTROLLER_H__
#define __UIVIEWCONTROLLER_H__

#include "lvgl.h"
#include "Utils.h"
#include "UIStack.h"
#include "UIVector.h"

extern UIKitType UI_NormalMode;
extern UIStackAddrDef uiStack;
extern UIVectorDef uiVector;

extern void viewInit(unsigned char * name, UIView * loadView);
extern void viewStackPush(unsigned char * name);
extern void viewStackPop();

#endif

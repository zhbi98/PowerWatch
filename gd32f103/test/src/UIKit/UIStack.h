
#ifndef __UISTACK_H__
#define __UISTACK_H__

#include <stdbool.h>
#include <string.h>
#include "UIKit.h"

#define STACK_SIZE_MAX 10

typedef struct {
    UIKitType buff[STACK_SIZE_MAX];
    int top;
} UIStackDef;

extern void stackInit(UIStackDef * s);
extern unsigned char stackPush(UIStackDef * s, UIKitType data);
extern unsigned char stackPop(UIStackDef * s, UIKitType * data);
extern unsigned char stackTop(UIStackDef * s, UIKitType * data);
extern unsigned char stackEmpty(UIStackDef * s);
extern unsigned char stackSize(UIStackDef * s);
extern unsigned char stackClear(UIStackDef * s);

/*****************************************
 *          ADDRESS STACK
 ****************************************/
typedef struct {
    UIKitType * buff[STACK_SIZE_MAX];
    int top;
} UIStackAddrDef;

extern void stackInitAddress(UIStackAddrDef * s);
extern unsigned char stackPushAddress(UIStackAddrDef * s, UIKitType * data);
extern unsigned char stackPopAddress(UIStackAddrDef * s, UIKitType ** data);
extern unsigned char stackTopAddress(UIStackAddrDef * s, UIKitType ** data);
extern unsigned char stackEmptyAddress(UIStackAddrDef * s);
extern unsigned char stackSizeAddress(UIStackAddrDef * s);
extern unsigned char stackClearAddress(UIStackAddrDef * s);

#endif

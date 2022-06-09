
#ifndef __UIVECTOR_H__
#define __UIVECTOR_H__

#include <stdbool.h>
#include <string.h>
#include "UIKit.h"

#define VEC_SIZE_MAX 10

typedef struct {
    UIKitType buff[VEC_SIZE_MAX];
    int index;
} UIVectorDef;

extern unsigned char vectorPush(UIVectorDef * v, UIKitType data);
extern UIKitType vectorGet(UIVectorDef * v, int index);
extern UIKitType * vectorGetAddress(UIVectorDef * v, int index);
extern int vectorSize(UIVectorDef * v);

#endif

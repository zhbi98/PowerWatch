
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "UIKit.h"
#include "UIStack.h"
#include "UIVector.h"

extern unsigned char stackFind(UIStackDef stack, unsigned char * name);
extern unsigned char stackFindAddress(UIStackAddrDef stack, unsigned char * name);
extern unsigned char vectorFind(UIVectorDef vec, unsigned char * name);
extern unsigned char vectorFindAddress(UIVectorDef * vec, unsigned char * name);
extern UIKitType vectorNameGet(UIVectorDef vec, unsigned char * name);
extern UIKitType * vectorNameGetAddress(UIVectorDef * vec, unsigned char * name);

#endif

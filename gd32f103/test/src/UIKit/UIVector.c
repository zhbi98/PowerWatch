
#include "UIVector.h"

unsigned char vectorPush(UIVectorDef * v, UIKitType data)
{
    if (v->index > VEC_SIZE_MAX - 1)
        return false;
    v->buff[v->index] = data;
    v->index++;
    return true;
}

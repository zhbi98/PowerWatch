
#include "UIVector.h"

unsigned char vectorPush(UIVectorDef * v, UIKitType data)
{
    if (v->index > VEC_SIZE_MAX - 1)
        return false;
    v->buff[v->index] = data;
    v->index++;
    return true;
}

UIKitType vectorGet(UIVectorDef * v, int index)
{
	if (index > VEC_SIZE_MAX - 1)
		return v->buff[0];
	return v->buff[index];
}

UIKitType * vectorGetAddress(UIVectorDef * v, int index)
{
	if (index > VEC_SIZE_MAX - 1)
		return &v->buff[0];
	return &v->buff[index];
}

int vectorSize(UIVectorDef * v)
{
	return v->index;
}

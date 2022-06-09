
#include "UIStack.h"

unsigned char stackPush(UIStackDef * s, UIKitType data)
{
    if (s->top >= STACK_SIZE_MAX - 1)
        return false;
    s->top++;
    s->buff[s->top] = data;
    return true;
}

unsigned char stackPop(UIStackDef * s, UIKitType * data)
{
    if (s->top <= -1)
        return false;
    *data = s->buff[s->top];
    s->top--;
    return true;
}

unsigned char stackTop(UIStackDef * s, UIKitType * data)
{
    if (s->top <= -1)
        return false;
    *data = s->buff[s->top];
    return true;
}

unsigned char stackEmpty(UIStackDef * s)
{
    if (s->top <= -1)
        return true;
    return false;
}

unsigned char stackSize(UIStackDef * s)
{
    return s->top - (-1);
}

unsigned char stackClear(UIStackDef * s)
{
    memset(s->buff, 0, s->top);
    s->top = -1;
}

/*****************************************
 *          ADDRESS STACK
 ****************************************/
unsigned char stackPushAddress(UIStackAddrDef * s, UIKitType * data)
{
    if (s->top >= STACK_SIZE_MAX - 1)
        return false;
    s->top++;
    s->buff[s->top] = data;
    return true;
}

unsigned char stackPopAddress(UIStackAddrDef * s, UIKitType ** data)
{
    if (s->top <= -1)
        return false;
    *data = s->buff[s->top];
    s->top--;
    return true;
}

unsigned char stackTopAddress(UIStackAddrDef * s, UIKitType ** data)
{
    if (s->top <= -1)
        return false;
    *data = s->buff[s->top];
    return true;
}

unsigned char stackEmptyAddress(UIStackAddrDef * s)
{
    if (s->top <= -1)
        return true;
    return false;
}

unsigned char stackSizeAddress(UIStackAddrDef * s)
{
    return s->top - (-1);
}

unsigned char stackClearAddress(UIStackAddrDef * s)
{
    memset(s->buff, 0, s->top);
    s->top = -1;
}


#include "Utils.h"

unsigned char stackFind(UIStackDef stack, unsigned char * name)
{
    UIKitType top;

    while (!stackEmpty(&stack)) {
        stackTop(&stack, &top);

        if (strcmp(name, top.pageName) == 0)
            return true;
        stackPop(&stack, &top);
    }
    return false;
}

unsigned char stackFindAddress(UIStackAddrDef stack, unsigned char * name)
{
    UIKitType * top;

    while (!stackEmptyAddress(&stack)) {
        stackTopAddress(&stack, &top);

        if (strcmp(name, top->pageName) == 0)
            return true;
        stackPopAddress(&stack, &top);
    }
    return false;
}

unsigned char vectorFind(UIVectorDef vec, unsigned char * name)
{
    unsigned char i = 0;

    while (i < vectorSize(&vec)) {
        if (strcmp(name, vectorGet(&vec, i).pageName) == 0)
            return true;
        i++;
    }
    return false;
}

UIKitType vectorNameGet(UIVectorDef vec, unsigned char * name)
{
    unsigned char i = 0;

    while (i < vectorSize(&vec)) {
        if (strcmp(name, vectorGet(&vec, i).pageName) == 0)
            return vectorGet(&vec, i);
        i++;
    }
    return vectorGet(&vec, 0);
}

UIKitType * vectorNameGetAddress(UIVectorDef * vec, unsigned char * name)
{
    unsigned char i = 0;

    while (i < vectorSize(vec)) {
        if (strcmp(name, vectorGetAddress(vec, i)->pageName) == 0)
            return vectorGetAddress(vec, i);
        i++;
    }
    return vectorGetAddress(vec, 0);
}


#include "Utils.h"

unsigned char stackFind(UIStackDef stack, UIKitType data)
{
    UIKitType top;
    size_t size;

    char buff1[64];
    char buff2[64];

    while (!stackEmpty(&stack)) {
        stackTop(&stack, &top);

        memcpy(buff1, &data, sizeof(UIKitType));
        memcpy(buff2, &top, sizeof(UIKitType));

        if (sizeof(UIKitType) > sizeof(UIKitType))
            size = sizeof(UIKitType);
        else
            size = sizeof(UIKitType);

        if (memcmp(buff1, buff2, size) == 0)
            return true;
        stackPop(&stack, &top);
    }
    return false;
}

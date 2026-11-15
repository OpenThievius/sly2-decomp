#include "sly2.h"

extern void *B_003E1060;

s32 FBlotObscured(char *arg0) {
    VECTOR local;
    char *node = (char *)B_003E1060;
    if (node != 0) {
        s32 key = *(s32 *)(arg0 + 0xA4);
        do {
            if (key < *(s32 *)(node + 0xA4)) {
                return 1;
            }
            node = *(char **)(node + 0xB4);
        } while (node != 0);
    }
    return 0;
}

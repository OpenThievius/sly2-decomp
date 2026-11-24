#include "sly2.h"

/* a blot in the modal list B_003E1060: sort key at 0xA4, list link at 0xB4 */
struct BLOTNODE {
    u8 unknown_0x0[0xA4];
    s32 order;
    u8 unknown_0xA8[0xC];
    BLOTNODE *next;
};

extern BLOTNODE *B_003E1060;

s32 FBlotObscured(BLOTNODE *blot) {
    VECTOR local;
    BLOTNODE *node = B_003E1060;
    if (node != 0) {
        s32 key = blot->order;
        do {
            if (key < node->order) {
                return 1;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}

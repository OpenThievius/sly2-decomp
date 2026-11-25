#include "fbsprite.h"

extern "C" {
s32 QueueSpriteInstanceSlots(SPRITELABEL *, s32, s32);

void func_002185F8(SPRITE *arg0, s32 arg1, s32 arg2) {
    s16 ilabel;

    ilabel = arg0->insts[arg1].ilabel;
    if (ilabel >= 0) {
        QueueSpriteInstanceSlots(&arg0->labels[ilabel], arg1, arg2);
    }
}

}

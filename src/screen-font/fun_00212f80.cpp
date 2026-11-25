#include "blot.h"
#include "blotsprite.h"
extern "C" void func_00218038(void *);
extern "C" void SeekSpriteInstanceTime(void *, float, int, int);

extern "C" void func_00212F80(float u, BLOT *blot, int label)
{
    if (label == 0x314) {
        func_00218038((BLOTSPRITE *)blot->asprite);
        return;
    }
    for (int i = 0; i < blot->csprite; i++) {
        BLOTSPRITE *sprite = &((BLOTSPRITE *)blot->asprite)[i];
        for (int j = 0; j < sprite->clabel; j++) {
            int last = -1;
            BLOTSPRITELABEL *plabel = &sprite->alabel[j];
            if (label == plabel->id) {
                for (int k = 0; k < sprite->cinstance; k++) {
                    if (sprite->ainstance[k].state != -1) last = k;
                }
                if (last >= 0) SeekSpriteInstanceTime(sprite, u, last, 0);
            }
        }
    }
}

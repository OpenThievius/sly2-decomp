#include "fbsprite.h"

extern "C" int FGetSpriteSlotTransform(BLOT *blot, int isprite, AFFINE2D *mat, RGBA *add, RGBA *mul, int count, SLOT *slots)
{
    if (slots == 0) {
        SPRITEINST *root = ((SPRITE *)blot->asprite)->insts;
        count = root->cslot;
        slots = root->aslot;
    }
    int i = 0;
    if (i < count) {
        SLOT *cur = slots;
        do {
            MOVIECHAR *chr = cur->pchar;
            if (chr != 0 && chr->type == 4) {
                if (isprite == chr->id) {
                    *mat = cur->xf;
                    *add = cur->rgbaAdd;
                    *mul = cur->rgbaMul;
                    return 1;
                }
                SPRITE *sp = (SPRITE *)(chr->id * sizeof(SPRITE) + (uptr)blot->asprite);
                SPRITEINST *inst = (SPRITEINST *)(cur->iinst * sizeof(SPRITEINST) + (uptr)sp->insts);
                if (FGetSpriteSlotTransform(blot, isprite, mat, add, mul, inst->cslot, inst->aslot)) return 1;
            }
            i++;
            cur++;
        } while (i < count);
    }
    return 0;
}

#include "fbsprite.h"
#include "sly2.h"
extern "C" int FStartSpriteLabelInstance(BLOT *, int, int, int, SLOT *);

void func_00213B00(BLOT *obj, int id)
{
    if (id == -1) return;
    for (int i = 0; i < obj->csprite; i++) {
        SPRITE *ent = &((SPRITE *)obj->asprite)[i];
        for (int j = 0; j < ent->clabel; j++) {
            SPRITELABEL *sub = &ent->labels[j];
            if (id != sub->id)
                continue;
            int any = 0;
            for (int k = 0; k < ent->cinstance; k++)
                if (ent->insts[k].ilabel != -1) any = 1;
            if (any) {
                FStartSpriteLabelInstance(obj, i, j, 0, 0);
                return;
            }
            ent->ilabelPending = j;
            return;
        }
    }
}

#include "blot.h"
#include "blotsprite.h"
#include "heapalloc.h"
#include "sly2.h"

void func_00213CD8(BLOT *blot, int id, QW *src)
{
    for (int i = 0; i < blot->csprite; i++) {
        BLOTSPRITE *sprite = &((BLOTSPRITE *)blot->asprite)[i];
        for (int j = 0; j < sprite->clabel; j++) {
            BLOTSPRITELABEL *plabel = &sprite->alabel[j];
            if (plabel->id != id)
                continue;
            if (sprite->transform == 0) {
                HEAPALLOC *heap = (HEAPALLOC *)blot->palloc;
                sprite->transform = (QW *)heap->Alloc(0x20, 0x1F);
            }
            QW *dst = sprite->transform;
            dst[0] = src[0];
            dst[1] = src[1];
            return;
        }
    }
}

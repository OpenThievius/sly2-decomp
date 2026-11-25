#include "sly2.h"
#include "fbsprite.h"
#include "blot.h"
extern "C" void func_00215960(MOVIECHAR *, SLOT *, int);
extern "C" void PrependSlEntry(SL *, SLOT *);

void QueueSpriteInstanceSlots(SPRITELABEL *label, int index, int alpha)
{
    SPRITEINST *inst = (SPRITEINST *)(index * sizeof(SPRITEINST) + (uptr)label->psprite->insts);
    SLOT *slots = inst->aslot;
    for (int slot = inst->cslot - 1; slot >= 0; slot--) {
        SLOT *entry = &slots[slot];
        if (entry->pchar != 0) {
            func_00215960(entry->pchar, entry, alpha);
        } else if (entry->maskMode == 4) {
            PrependSlEntry(&label->pblot->sl, entry);
        }
    }
}

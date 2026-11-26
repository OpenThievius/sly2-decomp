#include "sly2.h"
#include "fbsprite.h"
extern "C" {
void func_002158C0(MOVIECHAR *, SLOT *);
void InitDepthSlot(SLOT *);
void ClearSpriteKeySlots(SPRITELABEL *plabel, int ikey, int iinst)
{
    SPRITEKEY *pkey = &plabel->akey[ikey];
    SLOT *aslot = plabel->psprite->insts[iinst].aslot;
    for (int iclear = 0; iclear < pkey->cclear; iclear++) {
        SLOT *pslot = &aslot[pkey->aclear[iclear]];
        if (pslot->pchar != 0)
            func_002158C0(pslot->pchar, pslot);
        else
            InitDepthSlot(pslot);
    }
}
}

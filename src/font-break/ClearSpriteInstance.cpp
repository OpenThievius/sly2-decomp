// SPDX-License-Identifier: GPL-3.0-or-later
#include "fbsprite.h"
extern "C" void InitDepthSlot(SLOT *);
extern "C" void func_002158C0(MOVIECHAR *, SLOT *);
extern "C" void ClearSpriteInstance(SPRITE *psprite, int iinst)
{
    SPRITEINST *pinst = (SPRITEINST *)(iinst * 0x18 + (sptr)psprite->insts);
    int count = pinst->cslot;
    SLOT *aslot = pinst->aslot;
    for (int i = 0; i < count; i++) {
        SLOT *pslot = &aslot[i];
        if (pslot->pchar)
            func_002158C0(pslot->pchar, pslot);
        else
            InitDepthSlot(pslot);
    }
}

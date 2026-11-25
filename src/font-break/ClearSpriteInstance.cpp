// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
struct SPRITESLOT { u8 unknown_0x0[0x30]; void *pdepth; u8 unknown_0x34[0x3C]; };
struct SPRITEGROUP { int count; SPRITESLOT *aslot; u8 unknown_0x8[0x10]; };
struct SPRITES { u8 unknown_0x0[0x8]; SPRITEGROUP *agroup; };
extern "C" void InitDepthSlot(SPRITESLOT *);
extern "C" void func_002158C0(void *, SPRITESLOT *);
extern "C" void ClearSpriteInstance(SPRITES *psprites, int igroup)
{
    SPRITEGROUP *pgroup = (SPRITEGROUP *)(igroup * 0x18 + (sptr)psprites->agroup);
    int count = pgroup->count;
    SPRITESLOT *aslot = pgroup->aslot;
    for (int i = 0; i < count; i++) {
        SPRITESLOT *pslot = &aslot[i];
        if (pslot->pdepth)
            func_002158C0(pslot->pdepth, pslot);
        else
            InitDepthSlot(pslot);
    }
}

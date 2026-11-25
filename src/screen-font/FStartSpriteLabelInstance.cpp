/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
struct CHAR { int pad0; int kind; u8 unknown_0x8[0x8]; int isprite; };
struct SLOT { u8 unknown_0x0[0x10]; char pos[0x20]; CHAR *pchar; u8 unknown_0x34[0x24]; int iinst; u8 unknown_0x5C[0xC]; char sle[8]; };
struct INST { int cslot; SLOT *aslot; int pad[4]; };
struct SPRITE { u8 unknown_0x0[0x8]; INST *ainst; u8 unknown_0xC[0x24]; };
struct BLOT { u8 unknown_0x0[0x84]; SPRITE *psprite; };
extern "C" {
void StopSpriteInstance(SPRITE *, int);
void ClearSle(void *);
int IinstFindFreeSprite(SPRITE *);
void StartSpriteInstance(float, SPRITE *, int, int, void *, unsigned *, unsigned *);
int FStartSpriteLabelInstance(BLOT *pblot, int isprite, int ilabel, int cslot, SLOT *aslot)
{
    if (aslot == 0) {
        INST *root = pblot->psprite[0].ainst;
        cslot = root->cslot;
        aslot = root->aslot;
    }
    for (int islot = 0; islot < cslot; islot++) {
        SLOT *slot = &aslot[islot];
        CHAR *pchar = slot->pchar;
        if (pchar == 0 || pchar->kind != 4)
            continue;
        int iinst = slot->iinst;
        if (pchar->isprite == isprite) {
            StopSpriteInstance(&pblot->psprite[isprite], iinst);
            ClearSle(slot->sle);
            slot->iinst = IinstFindFreeSprite(&pblot->psprite[isprite]);
            unsigned argbaAdd[4];
            unsigned argbaMul[4];
            argbaAdd[0] = 0x7F7F7F7F;
            argbaMul[0] = 0xFFFFFFFF;
            StartSpriteInstance(0.0f, &pblot->psprite[isprite], ilabel, slot->iinst, slot->pos, argbaAdd, argbaMul);
            return 1;
        } else {
            INST *ainst = pblot->psprite[pchar->isprite].ainst;
            if (FStartSpriteLabelInstance(pblot, isprite, ilabel, ainst[iinst].cslot, ainst[iinst].aslot))
                return 1;
        }
    }
    return 0;
}
}

/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "fbsprite.h"
extern "C" {
void StopSpriteInstance(SPRITE *, int);
void ClearSle(void *);
int IinstFindFreeSprite(SPRITE *);
void StartSpriteInstance(float, SPRITE *, int, int, void *, unsigned *, unsigned *);
int FStartSpriteLabelInstance(BLOT *pblot, int isprite, int ilabel, int cslot, SLOT *aslot)
{
    if (aslot == 0) {
        SPRITEINST *root = ((SPRITE *)pblot->asprite)[0].insts;
        cslot = root->cslot;
        aslot = root->aslot;
    }
    for (int islot = 0; islot < cslot; islot++) {
        SLOT *slot = &aslot[islot];
        MOVIECHAR *pchar = slot->pchar;
        if (pchar == 0 || pchar->type != 4)
            continue;
        int iinst = slot->iinst;
        if (pchar->id == isprite) {
            StopSpriteInstance(&((SPRITE *)pblot->asprite)[isprite], iinst);
            ClearSle(&slot->pslNext);
            slot->iinst = IinstFindFreeSprite(&((SPRITE *)pblot->asprite)[isprite]);
            unsigned argbaAdd[4];
            unsigned argbaMul[4];
            argbaAdd[0] = 0x7F7F7F7F;
            argbaMul[0] = 0xFFFFFFFF;
            StartSpriteInstance(0.0f, &((SPRITE *)pblot->asprite)[isprite], ilabel, slot->iinst, &slot->xf, argbaAdd, argbaMul);
            return 1;
        } else {
            SPRITEINST *ainst = ((SPRITE *)pblot->asprite)[pchar->id].insts;
            if (FStartSpriteLabelInstance(pblot, isprite, ilabel, ainst[iinst].cslot, ainst[iinst].aslot))
                return 1;
        }
    }
    return 0;
}
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "fbsprite.h"
extern "C" void PauseAmb(AMB *);

extern "C" void PauseSpriteInstance(SPRITE *psprite, int iinst)
{
    psprite->insts[iinst].fPaused = 1;
    if (psprite->insts[iinst].ramb) PauseAmb(psprite->insts[iinst].ramb);
}

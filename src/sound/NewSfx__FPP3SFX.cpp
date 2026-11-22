// SPDX-License-Identifier: GPL-3.0-or-later
#include "alloc.h"
/* a sound effect (retail names it SFX): id -1 (none), range 300 to 3000, volume 1.0; no reader gives the
   fields more than the constructor's stores, so they stay unnamed beyond their values */
struct SFX { s32 sfxid; f32 lmMin; f32 lmMax; f32 volume; u8 unknown_0x10[4]; };
extern "C" {
char *PvAllocSwClearImpl__Fi(ALLOCREQ *);
SFX *NewSfx__FPP3SFX(void)
{
    ALLOCREQ req;
    req.cb = 0x14;
    req.cbAlign = 0x10;
    SFX *psfx = (SFX *)PvAllocSwClearImpl__Fi(&req);
    psfx->sfxid = -1;
    psfx->lmMin = 300.0f;
    psfx->lmMax = 3000.0f;
    psfx->volume = 1.0f;
    return psfx;
}
}

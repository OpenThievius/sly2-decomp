// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "asega.h"
struct ALO;

// the direction-animation set of a kind-3 ANIMREF (0xD0 bytes): the animation it plays is at 0x30
struct DIRANIMS {
    u8 unknown_0x0[0x30];
    ASEG *paseg;
};

// a playing direction animation, 0x40 bytes, the pinst of a kind-3 ANIMREF
struct DIRANIM {
    s32 field_0x0;
    s32 field_0x4;
    u8 unknown_0x8[0x4];
    void *pvtable;
    u8 unknown_0x10[0x10];
    ALO *palo;
    ASEGA *pasega;
    DIRANIMS *pdiranims;
    ASEG **ppasegCurrent;
    u32 grfapl;
};

extern char D_002DA9D0[];
extern "C" void ApplyAsegToHandle(float, float, ASEG *, ALO *, int, ASEGA **);
extern "C" void SubscribeLoObject(void *, void *);

void StartDirAnim(DIRANIMS *pdiranims, ALO *palo, int grfapl, DIRANIM *pdiranim)
{
    memset(pdiranim, 0, 0x40);
    memset(pdiranim, 0, 0x40);
    pdiranim->pdiranims = pdiranims;
    pdiranim->palo = palo;
    pdiranim->pvtable = D_002DA9D0;
    pdiranim->grfapl = grfapl;
    pdiranim->field_0x0 = 0;
    pdiranim->field_0x4 = 0;
    ApplyAsegToHandle(0.0f, 1.0f, pdiranims->paseg, palo, grfapl, &pdiranim->pasega);
    SubscribeLoObject(pdiranim->pasega, pdiranim);
    pdiranim->ppasegCurrent = &pdiranims->paseg;
}

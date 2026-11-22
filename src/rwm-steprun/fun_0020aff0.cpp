// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"

extern "C" {
void ResetAnimref(ANIMREF *, STEPGUARD *);
void func_0020BD78(JUMPANIM *);
JUMPANIM *func_0020C010(u32);

void func_0020AFF0(AIMSTATE *paim, s32 id) {
    JUMPANIM *pjumpanim;
    ANIMREF *panimref;

    panimref = &paim->animref;
    ResetAnimref(panimref, paim->pguard);
    paim->animref.kind = 2;
    pjumpanim = func_0020C010(0x40);
    panimref->pdata = pjumpanim;
    func_0020BD78(pjumpanim);
    ((JUMPANIM *)panimref->pdata)->field_0x0 = id;
    panimref->grf = 0;
}

}

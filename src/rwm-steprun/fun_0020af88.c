// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"

void BindAnimref(struct ANIMREF *panimref, struct STEPGUARD *pguard);
void ResetAnimref(struct ANIMREF *panimref, struct STEPGUARD *pguard);

void func_0020AF88(struct AIMSTATE *paim, void *pdata, u32 grf) {
    struct ANIMREF *panimref;

    panimref = &paim->animref;
    ResetAnimref(panimref, paim->pguard);
    paim->animref.pdata = pdata;
    paim->animref.grf = grf;
    BindAnimref(panimref, paim->pguard);
}

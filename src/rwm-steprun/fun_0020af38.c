// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"

void ResetAnimref(struct ANIMREF *panimref, struct STEPGUARD *pguard);

void func_0020AF38(struct AIMSTATE *paim, void *pdata, u32 grf) {
    ResetAnimref(&paim->animref, paim->pguard);
    paim->animref.pdata = pdata;
    paim->animref.grf = grf;
}

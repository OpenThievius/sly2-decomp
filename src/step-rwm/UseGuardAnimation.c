/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

s32 GrfsgsFromRef(s32);
struct GUARDANIM *PguardanimEnsure(struct STEPGUARDVIEW *, s64);

void UseGuardAnimation(struct STEPGUARDVIEW *pguard, s32 refList, void *pdata, u32 grf) {
    struct GUARDANIM *panim;

    panim = PguardanimEnsure(pguard, GrfsgsFromRef(refList));
    panim->ref.pdata = pdata;
    panim->ref.grf = grf;
}

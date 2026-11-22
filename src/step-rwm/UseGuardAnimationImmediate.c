/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

void BindAnimref(struct ANIMREF *, struct STEPGUARDVIEW *);
s32 GrfsgsFromRef(s32);
struct GUARDANIM *PguardanimEnsure(struct STEPGUARDVIEW *, s64);
void UseGuardAnimation(struct STEPGUARDVIEW *, s32, void *, u32);

void UseGuardAnimationImmediate(struct STEPGUARDVIEW *pguard, s32 refList, void *pdata, u32 grf) {
    struct GUARDANIM *panim;

    panim = PguardanimEnsure(pguard, GrfsgsFromRef(refList));
    UseGuardAnimation(pguard, refList, pdata, grf);
    BindAnimref(&panim->ref, pguard);
}

/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

s32 FIsBasicDerivedFrom(void *, s32);
s32 func_0020A298(struct STEPGUARDVIEW *, struct LO *, u64);
extern s32 B_002DD648;

s32 func_0020A378(struct STEPGUARDVIEW *pguard, struct LO *plo, u64 grfsgs) {
    if ((FIsBasicDerivedFrom(plo, 0x36) != 0) && (FIsBasicDerivedFrom(pguard, 0x3A) == 0) && (FIsBasicDerivedFrom(pguard, 0x3D) == 0) && ((sptr)pguard != B_002DD648)) {
        return 1;
    }
    return func_0020A298(pguard, plo, grfsgs);
}

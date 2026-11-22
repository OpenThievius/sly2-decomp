/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

s32 FIsSgsInGrfsgs(s64, s32);                       /* extern */

s32 FIsGuardInSgs(struct STEPGUARDVIEW *pguard, s32 sgs) {
    return FIsSgsInGrfsgs(pguard->grfsgs, sgs);
}

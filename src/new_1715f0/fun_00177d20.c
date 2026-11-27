/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "guardview.h"

s32 func_00177D20(struct GOALBRAIN *goal) {
    struct STEPGUARDVIEW *pguard;
    s32 result;

    pguard = (struct STEPGUARDVIEW *)goal->pstep;
    result = 0;
    if ((pguard->field_0xFA8 != 0) || (pguard->field_0xF94 != 0)) {
        result = 1;
    }
    return result;
}

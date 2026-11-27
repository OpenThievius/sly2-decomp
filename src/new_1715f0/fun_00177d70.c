/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "guardview.h"

s32 FIsBasicDerivedFrom(void *pbasic, s32 classIndex);

s32 func_00177D70(struct GOALBRAIN *goal) {
    s32 result;

    result = 0;
    if (FIsBasicDerivedFrom(goal->pstep, 0x3C) != 0) {
        result = ((struct ZONEGUARDVIEW *)goal->pstep)->ploCommand != 0;
    }
    return result;
}

/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

void func_00174950(struct GOALTRACK *goal);

void func_001751F0(struct GOALTRACK *goal) {
    struct ANIMREF *panimref;

    ((struct STEPGUARDVIEW *)goal->pstep)->fFlag = 1;
    func_00174950(goal);
    panimref = goal->panimref;
    if (panimref->kind == 2) {
        ((struct JUMPER *)panimref->pinst)->fTrackTarget = 1;
        ((struct JUMPER *)goal->panimref->pinst)->field_0x64 = 1;
        goal->fTrackTarget = 1;
    }
}

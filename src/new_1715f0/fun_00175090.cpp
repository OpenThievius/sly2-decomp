// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "step.h"
extern "C" {
void SetXfKind(SO *pso, XF *pxf, s32 kind);
void func_00174B28(GOALANIM *goal);

void func_00175090(GOALANIM *goal) {
    func_00174B28(goal);
    STEP *pstep = goal->pstep;
    SetXfKind(pstep, pstep->pxfLinear, 2);
    if (goal->ptarget == 0) {
        pstep = goal->pstep;
        SetXfKind(pstep, pstep->pxfAngular, 2);
    }
}

}

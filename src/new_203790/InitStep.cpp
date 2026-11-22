// SPDX-License-Identifier: GPL-3.0-or-later
#include "step.h"
#include "goals.h"
extern "C" {
void GoalStack_Init(GOALSTACK *pgoalstack, STEP *pstep);
void InitPo(STEP *pstep);
void SetStepRadTarget(STEP *pstep, f32 radTarget);
}
f32 SetStepSpinRatio(STEP *pstep, f32 ratio);

extern "C" void InitStep(STEP *pstep) {
    InitPo(pstep);
    pstep->keyHull = -1;
    pstep->field_0x260 = 1.0f;
    pstep->field_0x200 = 1.0f;
    SetStepSpinRatio(pstep, 1.0f);
    SetStepRadTarget(pstep, 0.0f);
    pstep->field_0x220 = 30.0f;
    pstep->field_0x214 = -50.0f;
    GoalStack_Init(pstep->pgoalstack(), pstep);
}

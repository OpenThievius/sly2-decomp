// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
extern "C" int FIsGuardInSgs(void *, int);
extern "C" char *func_00205458(void *, int);
extern "C" void func_0017A8C8(void *, int);
extern "C" void GoalAnimLeap_SetState(void *, int);
extern "C" QW LimitVectorLength__FP6VECTORfT0(QW, float);
extern "C" float D_002C3DA8;
#include "stepguard.h"
void func_00209EE0(STEPGUARD *g)
{
    if (FIsGuardInSgs(g, 0x12) || FIsGuardInSgs(g, 0x13)) {
        func_0017A8C8(func_00205458(g, 0xB0), 2);
    } else if (FIsGuardInSgs(g, 0x17)) {
        char *goal = func_00205458(g, 0xB1);
        int s = *(int *)(goal + 0x50);
        if (s != 3 && s != 6) GoalAnimLeap_SetState(goal, 2);
    } else {
        return;
    }
    QW v = g->GetVelocityVec();
    QW l = LimitVectorLength__FP6VECTORfT0(v, D_002C3DA8);
    g->Slot35(l);
}

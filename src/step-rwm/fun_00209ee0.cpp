// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
extern "C" int FIsGuardInSgs(STEPGUARD *, int);
extern "C" GOAL *func_00205458(STEPGUARD *, int);
extern "C" void func_0017A8C8(GOALB0 *, int);
extern "C" void GoalAnimLeap_SetState(GOALGRAB *, int);
extern "C" QW LimitVectorLength__FP6VECTORfT0(QW, float);
extern "C" float D_002C3DA8;
void func_00209EE0(STEPGUARD *guard)
{
    if (FIsGuardInSgs(guard, 0x12) || FIsGuardInSgs(guard, 0x13)) {
        func_0017A8C8((GOALB0 *)func_00205458(guard, 0xB0), 2);
    } else if (FIsGuardInSgs(guard, 0x17)) {
        GOALGRAB *goal = (GOALGRAB *)func_00205458(guard, 0xB1);
        int phase = goal->phase;
        if (phase != 3 && phase != 6) GoalAnimLeap_SetState(goal, 2);
    } else {
        return;
    }
    QW velocity = guard->GetVelocityVec();
    QW limited = LimitVectorLength__FP6VECTORfT0(velocity, D_002C3DA8);
    guard->Slot35(limited);
}

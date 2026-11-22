// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" {
void AddGuardSgs(STEPGUARD *pguard, s32 sgs);
void GoalAnim_SetState(GOALANIM *goal, s32 state);
GUARDANIM *PguardanimCurrent(STEPGUARD *pguard);
void func_001EEF70();

void func_00174950(GOALANIM *goal) {
    func_001EEF70();
    AddGuardSgs(GOAL_GUARD(goal), goal->sgs);
    if (goal->panimref == 0) {
        goal->panimref = &PguardanimCurrent(GOAL_GUARD(goal))->ref;
        if (goal->panimref == 0) {
            GoalAnim_SetState(goal, 1);
            return;
        }
    }
    GoalAnim_SetState(goal, 0);
}

}

/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void Goal_Deactivate(void);
void RemoveGuardSgs(struct STEPGUARD *pguard, s32 sgs);
void SetSearchGoal(struct GOALSEARCH *goal, struct GOAL *pgoalSearch);
void SetSearchState(struct GOALSEARCH *goal, s32 state);

void func_00171FD0(struct GOALSEARCH *goal) {
    Goal_Deactivate();
    SetSearchState(goal, -1);
    RemoveGuardSgs(GOAL_GUARD(goal), 0x1F);
    SetSearchGoal(goal, 0);
}

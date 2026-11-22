/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void GoalAnim_SetState(struct GOALANIM *goal, s32 state);
void Goal_Deactivate(void);
void RemoveGuardSgs(struct STEPGUARD *pguard, s32 sgs);

void func_00174B28(struct GOALANIM *goal) {
    Goal_Deactivate();
    GoalAnim_SetState(goal, 1);
    RemoveGuardSgs(GOAL_GUARD(goal), goal->sgs);
}

/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void GoalNotice_SetState(struct GOALNOTICE *goal, s32 state);
void Goal_Deactivate(void);
void RemoveGuardSgs(struct STEPGUARD *pguard, s32 sgs);

void func_001757D0(struct GOALNOTICE *goal) {
    Goal_Deactivate();
    GoalNotice_SetState(goal, -1);
    RemoveGuardSgs(GOAL_GUARD(goal), 0x1D);
}

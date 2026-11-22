/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void GoalNotice_SetState(struct GOALNOTICE *goal, s32 state);
void func_001EEF70(void);
void func_00208540(struct STEPGUARD *pguard, struct LO *ptarget);

void func_00175790(struct GOALNOTICE *goal) {
    func_001EEF70();
    GoalNotice_SetState(goal, 3);
    func_00208540(GOAL_GUARD(goal), goal->ptarget);
}

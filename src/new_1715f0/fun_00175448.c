/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void Goal_Deactivate(void);
void RemoveGuardSgs(struct STEPGUARD *pguard, s32 sgs);
void func_00175488(struct GOALREACT *goal, s32 state);

void func_00175448(struct GOALREACT *goal) {
    Goal_Deactivate();
    func_00175488(goal, -1);
    RemoveGuardSgs(GOAL_GUARD(goal), 0x18);
}

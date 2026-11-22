// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" {
void AddGuardSgs(STEPGUARD *pguard, s32 sgs);
void func_001EEF68();

void func_00171F58(GOALSEARCH *goal) {
    func_001EEF68();
    AddGuardSgs(GOAL_GUARD(goal), 0x1F);
    goal->state = -1;
    goal->field_0x38 = 3.4028235e38f;
    goal->field_0x40 = 3.4028235e38f;
}

}

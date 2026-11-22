/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

s32 GoalGoto_FArrived(struct GOAL *pgoal);
void func_0017ECF0(struct GOALFOLLOWCURVE *pgoal, s32 force);
void func_001EEF98(struct GOALFOLLOWCURVE *pgoal);

void func_0017ECB0(struct GOALFOLLOWCURVE *pgoal) {
    func_001EEF98(pgoal);
    if (GoalGoto_FArrived(pgoal->pgoalChild) != 0) {
        func_0017ECF0(pgoal, 0);
    }
}

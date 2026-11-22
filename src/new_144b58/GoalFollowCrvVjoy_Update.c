/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

void GoalFollowCrv_Update(struct GOALFOLLOWCRVVJOY *pgoal);
void func_001448F0(u8 *pvjoy, QW posGoal);

void GoalFollowCrvVjoy_Update(struct GOALFOLLOWCRVVJOY *pgoal) {
    GoalFollowCrv_Update(pgoal);
    func_001448F0(GOAL_JT(pgoal)->vjoy, pgoal->posGoal);
}

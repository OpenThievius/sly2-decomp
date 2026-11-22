/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

void GoalFollowCrv_Activate(struct GOALFOLLOWCRVVJOY *pgoal);
void func_001448F0(u8 *pvjoy, QW posGoal);

void GoalFollowCrvVjoy_Activate(struct GOALFOLLOWCRVVJOY *pgoal) {
    GoalFollowCrv_Activate(pgoal);
    func_001448F0(GOAL_JT(pgoal)->vjoy, pgoal->posGoal);
}

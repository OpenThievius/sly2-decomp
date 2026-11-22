// SPDX-License-Identifier: GPL-3.0-or-later
#include "goals.h"
extern "C" void GoalGoto_Replan(GOALGOTO *);
void SetGoalTarget(GOALGOTO *pgoal, GOALTARGET *ptarget)
{
    pgoal->target = *ptarget;
    pgoal->field_0xA0 = -3.402823466e+38f;
    GoalGoto_Replan(pgoal);
}

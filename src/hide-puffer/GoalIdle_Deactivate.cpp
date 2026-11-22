// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" {

void GoalIdle_SetState(GOALIDLE *pgoal, int state);
void Goal_Deactivate(GOAL *pgoal);
void RemoveGuardSgs(STEPGUARD *pguard, int sgs);

void GoalIdle_Deactivate(GOALIDLE *pgoal) {
    GoalIdle_SetState(pgoal, -1);
    Goal_Deactivate(pgoal);
    RemoveGuardSgs((STEPGUARD *)pgoal->pstep, 0x1E);
}
}

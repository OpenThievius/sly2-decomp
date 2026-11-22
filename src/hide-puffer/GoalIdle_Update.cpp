// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "clock.h"
extern "C" {
int FGuardScriptDone(GOAL *pgoalChild);
void GoalIdle_SetState(GOALIDLE *, int);
int func_00209098(STEPGUARD *);
int func_001EF0A8(GOAL *);
void func_001EEF98(GOAL *);
}
extern "C" void GoalIdle_Update(GOALIDLE *pgoal)
{
    func_001EEF98(pgoal);
    int canAlert = func_00209098((STEPGUARD *)pgoal->pstep);
    while (func_001EF0A8(pgoal) == 0) {
        int previousState = pgoal->state;
        switch (previousState) {
        case 1:
            if (canAlert == 0) {
                if (g_2dded0.t > pgoal->tWaitLimit)
                    GoalIdle_SetState(pgoal, 0);
            } else {
                GoalIdle_SetState(pgoal, 3);
            }
            break;
        case 2:
            if (canAlert != 0)
                GoalIdle_SetState(pgoal, 3);
            break;
        case 0:
            if (canAlert != 0) {
                GoalIdle_SetState(pgoal, 3);
            } else if (g_2dded0.t > pgoal->tScriptLimit) {
                GoalIdle_SetState(pgoal, 1);
            } else if (FGuardScriptDone(pgoal->pgoalChild) != 0) {
                pgoal->pscript = 0;
                GoalIdle_SetState(pgoal, 2);
            }
            break;
        case 3:
            if (canAlert == 0) {
                if (pgoal->pscript != 0)
                    GoalIdle_SetState(pgoal, 1);
                else
                    GoalIdle_SetState(pgoal, 2);
            }
            break;
        }
        if (pgoal->state == previousState)
            break;
    }
}

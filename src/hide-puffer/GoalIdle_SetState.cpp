// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "clock.h"
extern "C" {
void func_00171C18(GOAL *pgoalChild, u8 *scratch);
void Goal_Pop(GOAL **);
GOAL *func_00205438(STEPGUARD *, int);
void SetGuardScript(GOAL *pscriptGoal, void *pscript, int flags, u8 *scratch);
void func_00179E80(GOALIDLE *);
void func_00179EF8(GOALIDLE *);
}
extern const float D_002A5590;
extern "C" void GoalIdle_SetState(GOALIDLE *pgoal, int newState)
{
    if (newState == pgoal->state)
        return;
    if (pgoal->state == 0)
        func_00171C18(pgoal->pgoalChild, ((STEPGUARD *)pgoal->pstep)->scratch);
    Goal_Pop(&pgoal->pgoalChild);
    pgoal->state = newState;
    pgoal->tState = g_2dded0.t;
    switch (newState) {
    case 1:
    case 2: {
        GOAL *pwait = func_00205438((STEPGUARD *)pgoal->pstep, 0x9E);
        pwait->Activate();
        func_00179EF8(pgoal);
        pgoal->tScriptLimit = D_002A5590;
        break;
    }
    case 0: {
        GOAL *pscriptGoal = func_00205438((STEPGUARD *)pgoal->pstep, 0xA9);
        SetGuardScript(pscriptGoal, pgoal->pscript, 0, ((STEPGUARD *)pgoal->pstep)->scratch);
        pscriptGoal->Activate();
        func_00179E80(pgoal);
        pgoal->tWaitLimit = D_002A5590;
        break;
    }
    case 3: {
        GOALANIM *pwait = (GOALANIM *)func_00205438((STEPGUARD *)pgoal->pstep, 0x9E);
        pwait->sgs = 1;
        pwait->Activate();
        break;
    }
    }
}

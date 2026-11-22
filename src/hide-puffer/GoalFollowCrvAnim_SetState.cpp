// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "clock.h"
extern "C" float g_2be694;
extern "C" void GoalFollowCrv_SetState(GOALFOLLOWCRV *, int);
extern "C" void Goal_Pop(GOAL **);
extern "C" GOAL *func_00205438(STEPGUARD *, int);
extern "C" QW PosLoWorld(void *);
extern "C" void GoalFollowCrvAnim_SetState(GOALFOLLOWCRVANIM *pgoal, int state)
{
    unsigned stateOld = pgoal->state;
    if (state == stateOld)
        return;
    GoalFollowCrv_SetState(pgoal, state);
    switch (pgoal->state) {
    case 0:
    case 1:
        if (stateOld > 1) {
            Goal_Pop(&pgoal->pgoalChild);
            GOALANIM *pidle = (GOALANIM *)func_00205438((STEPGUARD *)pgoal->pstep, 0x9D);
            pidle->sgs = pgoal->kind;
            if (pgoal->kind == 8)
                pidle->ptarget = pgoal->ptarget;
            pidle->Activate();
            pgoal->posLast = PosLoWorld(pgoal->pstep);
            pgoal->tStuck = g_2be694;
        }
        break;
    case 2:
    case 3:
    case 4:
        if (stateOld != 2 && stateOld != 4 && stateOld != 3) {
            Goal_Pop(&pgoal->pgoalChild);
            GOALANIM *palert = (GOALANIM *)func_00205438((STEPGUARD *)pgoal->pstep, 0x9E);
            palert->ptarget = pgoal->ptarget;
            palert->Activate();
        }
        break;
    }
}

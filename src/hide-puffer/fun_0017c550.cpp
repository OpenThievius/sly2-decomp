// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
struct GOAL_17C550 : GOAL {
    int state;
};
extern "C" void Goal_Pop(void *);
extern "C" GOAL *func_00205438(STEPGUARD *, int);
extern "C" void GoalFollowCrv_SetCrv(GOALFOLLOWCRV *, CRV *, int);
void func_0017C550(GOAL_17C550 *pgoal, int nState)
{
    if (nState == pgoal->state)
        return;
    Goal_Pop(&pgoal->pgoalChild);
    pgoal->state = nState;
    switch (nState) {
    case 0: {
        GOALANIM *pobj = (GOALANIM *)func_00205438(((STEPGUARD *)pgoal->pstep), 0x9E);
        pobj->ptarget = ((STEPGUARD *)pgoal->pstep)->palert->palo;
        pobj->Activate();
        break;
    }
    case 1: {
        GOALFOLLOWCRVANIM *pobj = (GOALFOLLOWCRVANIM *)func_00205438(((STEPGUARD *)pgoal->pstep), 0xA7);
        GoalFollowCrv_SetCrv(pobj, (CRV *)((STEPGUARD *)pgoal->pstep)->pcrv, 0);
        pobj->kind = 8;
        pobj->ptarget = ((STEPGUARD *)pgoal->pstep)->palert->palo;
        pobj->Activate();
        break;
    }
    }
}

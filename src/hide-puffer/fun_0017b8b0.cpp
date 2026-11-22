// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "clock.h"
extern "C" void Goal_Pop(GOAL **);
extern "C" GOAL *func_00205438(STEPGUARD *, int);
extern "C" void func_00208540(STEPGUARD *, int);
void func_0017B8B0(GOALB2 *pgoal, int newState)
{
    if (newState == pgoal->state)
        return;
    Goal_Pop(&pgoal->pgoalChild);
    pgoal->state = newState;
    pgoal->tState = g_2dded0.t;
    switch (newState) {
    case 0: {
        GOAL *pwatch = func_00205438((STEPGUARD *)pgoal->pstep, 0x9e);
        pwatch->Activate();
        func_00208540((STEPGUARD *)pgoal->pstep, 0);
        break;
    }
    case 1: {
        GOALNOTICE *pturn = (GOALNOTICE *)func_00205438((STEPGUARD *)pgoal->pstep, 0xa5);
        pturn->ptarget = pgoal->ppick;
        pturn->field_0x40 = 1;
        pturn->Activate();
        break;
    }
    case 2: {
        GOALANIM *pwatch = (GOALANIM *)func_00205438((STEPGUARD *)pgoal->pstep, 0x9e);
        pwatch->sgs = 1;
        pwatch->Activate();
        break;
    }
    }
}

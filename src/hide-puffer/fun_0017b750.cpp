// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "clock.h"
extern "C" void Goal_Pop(GOAL **);
extern "C" GOAL *func_00205438(STEPGUARD *, int);
void func_0017B750(GOALSTAND *pgoal, int state)
{
    if (state == pgoal->state)
        return;
    Goal_Pop(&pgoal->pgoalChild);
    if (pgoal->state == 0) {
        ((STEPGUARD *)pgoal->pstep)->field_0xF60 = 0;
        pgoal->state = state;
    } else
        pgoal->state = state;
    pgoal->tState = g_2dded0.t;
    if (state == 0) {
        GOALANIM *panim = (GOALANIM *)func_00205438((STEPGUARD *)pgoal->pstep, 0x9D);
        panim->sgs = 0x11;
        panim->ptarget = pgoal->ptarget;
        panim->Activate();
        ((STEPGUARD *)pgoal->pstep)->field_0xF60 = 1;
    }
}

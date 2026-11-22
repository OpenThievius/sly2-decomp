// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
#include "clock.h"
extern "C" void Goal_Pop(GOAL **);
extern "C" GOAL *func_00205438(STEPGUARD *, int);
extern "C" void func_0017CD00(GOALB8 *pgoal, int state)
{
    if (state == pgoal->state)
        return;
    Goal_Pop(&pgoal->pgoalChild);
    pgoal->state = state;
    pgoal->tState = g_2dded0.t;
    if (state != 0) {
        if (state == 1) {
            GOALANIM *panim = (GOALANIM *)func_00205438(GOAL_GUARD(pgoal), 0x9D);
            panim->sgs = 2;
            panim->Activate();
        }
    } else {
        GOALANIM *panim = (GOALANIM *)func_00205438(GOAL_GUARD(pgoal), 0x9D);
        panim->sgs = 9;
        panim->Activate();
    }
}

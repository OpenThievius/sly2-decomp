// SPDX-License-Identifier: GPL-3.0-or-later
#include "clock.h"
#include "stepguard.h"
#include "goals.h"
extern "C" {
void Goal_Pop(GOAL **);
GOAL *func_00205438(STEP *, int);
void func_0017E0E0(GOALFLEE *);
}
extern "C" void func_0017E278(GOALFLEE *pgoal, int newState)
{
    if (newState == pgoal->state)
        return;
    Goal_Pop(&pgoal->pgoalChild);
    pgoal->state = newState;
    pgoal->tState = g_2dded0.t;
    switch (newState) {
    case 0: {
        GOALANIM *pidle = (GOALANIM *)func_00205438(pgoal->pstep, 0x9D);
        pidle->sgs = 0xB;
        pidle->ptarget = pgoal->ptarget;
        pidle->Activate();
        break;
    }
    case 1: {
        GOALGOTO *pgoto = (GOALGOTO *)func_00205438(pgoal->pstep, 0xBA);
        pgoto->fLink = 1;
        pgoto->field_0x38 = 0x1C;
        func_0017E0E0(pgoal);
        pgoto->Activate();
        break;
    }
    case 2: {
        GOALANIM *palert = (GOALANIM *)func_00205438(pgoal->pstep, 0x9E);
        palert->sgs = 1;
        palert->Activate();
        break;
    }
    }
}

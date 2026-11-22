// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "clock.h"
extern "C" {
void Goal_Pop(GOAL **);
GOAL *func_00205438(STEPGUARD *, int);
QW PosLoWorld(void *);
QW ConvertAloPos(void *, void *, QW);
void func_002562A8(GOALTARGET *);
void SetGoalTarget(GOAL *, GOALTARGET *);
}
extern "C" void func_0017C928(GOALGOTOTARGET *pgoal, int newState)
{
    if (newState == pgoal->state)
        return;
    Goal_Pop(&pgoal->pgoalChild);
    pgoal->state = newState;
    pgoal->tState = g_2dded0.t;
    switch (newState) {
    case 1: {
        GOALGOTO *pgoto = (GOALGOTO *)func_00205438((STEPGUARD *)pgoal->pstep, 0xBA);
        QW pos = PosLoWorld(pgoal->ptarget);
        pgoal->pos = pos;
        pgoto->fLink = 1;
        pgoto->ptarget = pgoal->ptarget;
        pgoto->field_0xAC = 1;
        GOALTARGET target;
        func_002562A8(&target);
        target.pos = pos;
        SetGoalTarget(pgoto, &target);
        pgoto->field_0x38 = 0x1C;
        pgoto->Activate();
        break;
    }
    case 2: {
        GOALANIM *palert = (GOALANIM *)func_00205438((STEPGUARD *)pgoal->pstep, 0x9E);
        LO *ptarget = pgoal->ptarget;
        palert->sgs = 1;
        palert->ptarget = ptarget;
        palert->Activate();
        break;
    }
    case 0: {
        GOALGOTO *pgoto = (GOALGOTO *)func_00205438((STEPGUARD *)pgoal->pstep, 0xBA);
        pgoal->pos = PosLoWorld(pgoal->ptarget);
        QW offset = ConvertAloPos(pgoal->ptarget, 0, pgoal->offset);
        pgoto->fLink = 1;
        GOALTARGET target;
        func_002562A8(&target);
        target.pos = offset;
        SetGoalTarget(pgoto, &target);
        pgoto->ptarget = pgoal->ptarget;
        pgoto->Activate();
        break;
    }
    }
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
extern "C" {
void Goal_Pop(GOAL **ppgoal);
GOAL *func_00205438(STEPGUARD *pguard, int classId);
QW PosLoWorld(LO *plo);
QW func_00172760(GOALSEARCH *goal);
void func_00172560(GOALSEARCH *goal);
void func_001728B0(GOALSEARCH *goal);
void func_00172F10(GOALSEARCH *goal);
void func_00209818(void *pactor, float angle);
float atan2f(float, float);
void func_002562A8(GOALTARGET *);
void SetGoalTarget(GOAL *, GOALTARGET *);
void SetSearchGoal(GOALSEARCH *, GOAL *);
}
extern "C" float g_2dded0[];
extern "C" const float RO_FLT_002A5398;
extern "C" void SetSearchState(GOALSEARCH *goal, int newState)
{
    if (newState == goal->state)
        return;
    Goal_Pop(&goal->pgoalChild);
    goal->state = newState;
    goal->tState = g_2dded0[0];
    switch (newState) {
    case 0: {
        GOALANIM *idle = (GOALANIM *)func_00205438(GOAL_GUARD(goal), 0x9D);
        idle->sgs = 0xC;
        idle->Activate();
        break;
    }
    case 1: {
        GOALGOTO *go = (GOALGOTO *)func_00205438(GOAL_GUARD(goal), 0xBA);
        go->fLink = 1;
        QW pos = func_00172760(goal);
        GOALTARGET t;
        func_002562A8(&t);
        t.pos = pos;
        SetGoalTarget(go, &t);
        go->Activate();
        goal->field_0x38 = RO_FLT_002A5398;
        break;
    }
    case 2: {
        QW goalPos = func_00172760(goal);
        QW pos = PosLoWorld(goal->pstep);
        QW difference = VectorSub(goalPos, pos);
        GUARDHEADING *pheading = &GOAL_GUARD(goal)->heading;
        float angle = atan2f(LaneYInGeneralRegister(difference), LaneX(difference));
        func_00209818(pheading, angle);
        GOAL *alert = func_00205438(GOAL_GUARD(goal), 0x9E);
        alert->Activate();
        func_00172560(goal);
        break;
    }
    case 3: {
        GOALGOTO *go = (GOALGOTO *)func_00205438(GOAL_GUARD(goal), 0xBA);
        go->fLink = 1;
        func_001728B0(goal);
        func_00172F10(goal);
        go->Activate();
        break;
    }
    case 4: {
        GOALANIM *idle = (GOALANIM *)func_00205438(GOAL_GUARD(goal), 0x9D);
        idle->sgs = 0xE;
        idle->Activate();
        SetSearchGoal(goal, 0);
        goal->fChanged = 0;
        break;
    }
    case 5: {
        GOALANIM *alert = (GOALANIM *)func_00205438(GOAL_GUARD(goal), 0x9E);
        alert->sgs = 1;
        alert->Activate();
        break;
    }
    }
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
#include "clock.h"
extern "C" void Goal_Pop(GOAL **);
extern "C" GOAL *func_00205438(STEPGUARD *, int);
extern "C" void GoalFollowCrv_SetCrv(GOAL *, void *, int);
// Retail computes the follow mode straight into $v0 with three branches (9 in the first two delay slots, 8 in
// the last one, 9 on fall-through) and one store at the join: two stores in an if/else, which gcc merges at the
// join without if-converting to movn. A local `mode` assigned in both arms becomes movn or a bnel store instead.
extern "C" void GoalGoto_SetState(GOALGOTO *goal, int newState)
{
    int previous = goal->state;
    if (newState == previous)
        return;
    if (newState >= 0 && newState < 3 && previous >= 0 && previous < 3) {
        goal->state = newState;
    } else {
        Goal_Pop(&goal->pgoalChild);
        goal->state = newState;
    }
    goal->tState = g_2dded0.t;
    switch (newState + 1) {
    case 0:
    case 1:
        break;
    case 5: {
        GOALANIM *hold = (GOALANIM *)func_00205438(GOAL_GUARD(goal), 0x9E);
        hold->ptarget = goal->ptarget;
        hold->Activate();
        break;
    }
    case 4: {
        GOALFOLLOWROUTE *route = (GOALFOLLOWROUTE *)func_00205438(GOAL_GUARD(goal), 0xBE);
        route->proute = (ROUTE *)goal->apzlink[0];
        route->Activate();
        break;
    }
    case 2:
    case 3: {
        GOALFOLLOWCRVANIM *follow = (GOALFOLLOWCRVANIM *)goal->pgoalChild;
        if (follow == 0) {
            follow = (GOALFOLLOWCRVANIM *)func_00205438(GOAL_GUARD(goal), 0xA7);
            follow->ptarget = goal->ptarget;
            follow->field_0x40 = goal->fStraight;
            if (goal->ptarget != 0 && goal->field_0xAC == 0 && (GOAL_GUARD(goal)->grf & 4) != 0)
                follow->kind = 8;
            else
                follow->kind = 9;
            GoalFollowCrv_SetCrv(follow, GOAL_GUARD(goal)->pcrv, 0);
            follow->Activate();
            break;
        }
        GoalFollowCrv_SetCrv(follow, GOAL_GUARD(goal)->pcrv, 0);
        break;
    }
    case 6: {
        GOALSNAPTOPOINT *snap = (GOALSNAPTOPOINT *)func_00205438(GOAL_GUARD(goal), 0xBF);
        snap->target = goal->targetSnap;
        snap->Activate();
        break;
    }
    }
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "vu0inline.h"
#include "ps2inline.h"
#include "step.h"
#include "clock.h"
#include "stepguard.h"
#include "goals.h"
/* the curve the guard walks (STEP::pcrv): mode, and a pointer to its control points */
struct CRVHOLDER { u8 unknown_0x0[0xE8]; s32 mode; u8 unknown_0xEC[0x8]; QW *points; };
extern "C" {
void Goal_Pop(GOAL **);
GOAL *func_00205438(STEP *, int);
QW PosLoWorld(STEP *);
QW func_001C1EC0(GOALTARGET *, QW);
void MeasureCrv(CRVHOLDER *);
void GoalFollowCrv_SetCrv(GOALFOLLOWCRV *, CRVHOLDER *, int);
void func_0017E628(GOALFOLLOWROUTE *);
}
extern float g_2be7b0;
extern float g_2be7b4;
extern "C" void func_0017E6B0(GOALFOLLOWROUTE *pgoal, int newState)
{
    if (newState == pgoal->state)
        return;
    Goal_Pop(&pgoal->pgoalChild);
    pgoal->state = newState;
    pgoal->tState = g_2dded0.t;
    switch (newState) {
    case 0:
        switch (pgoal->proute->kind) {
        case 0: {
            GOALFOLLOWCRVANIM *pfollow = (GOALFOLLOWCRVANIM *)func_00205438(pgoal->pstep, 0xA7);
            CRVHOLDER *pcrv = (CRVHOLDER *)pgoal->pstep->pcrv;
            QW pos = PosLoWorld(pgoal->pstep);
            QW goal = func_001C1EC0(&pgoal->proute->awaypoint[pgoal->index], pos);
            float distance = LaneX(SqrtX(SquaredLengthXy(VectorSub(pos, goal))));
            float scaled = distance / g_2be7b0;
            float clamped = scaled < g_2be7b4 ? g_2be7b4 : scaled;
            pgoal->tEnd = g_2dded0.t + clamped;
            pcrv->mode = 2;
            pcrv->points[0] = pos;
            pcrv->points[1] = goal;
            MeasureCrv(pcrv);
            pfollow->field_0x40 = 1;
            pfollow->field_0x64 = 10.0f;
            GoalFollowCrv_SetCrv(pfollow, pcrv, 0);
            pfollow->Activate();
            break;
        }
        case 1:
            func_0017E628(pgoal);
            break;
        }
        break;
    case 1: {
        GOALSNAPTOPOINT *pgoto = (GOALSNAPTOPOINT *)func_00205438(pgoal->pstep, 0xBF);
        ROUTE *pslot = (ROUTE *)(pgoal->index * sizeof(GOALTARGET) + (sptr)pgoal->proute); /* the index first: retail adds the scaled index to the route, then loads at +0x60 */
        pgoto->target = pslot->awaypoint[0];
        pgoto->Activate();
        break;
    }
    }
}

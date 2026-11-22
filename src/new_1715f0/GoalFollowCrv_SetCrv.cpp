// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
/* the curve this goal follows: only its closed flag is read here */
struct CRV {
    u8 unknown_0x0[0xE4];
    /* 0xE4 */ s32 closed;
};
extern "C" char B_003DD020;
extern "C" QW PosLoWorld(LO *plo);
extern "C" void FindCrvClosestPointFromS(CRV *, QW, void *, int, int, int, float *, float);
extern "C" void FindCrvClosestPointAll(CRV *, QW, void *, int, int, int, float *);
extern "C" float SMinCrv(CRV *);
extern "C" float SMaxCrv(CRV *);
extern "C" void GetPathPosFromS(CRV *, void *, int, float);
extern "C" void GoalFollowCrv_SetCrv(GOALFOLLOWCRV *goal, CRV *crv, int reverse)
{
    goal->reverse = reverse;
    goal->pcrv = crv;
    if (goal->sHint >= 0.0f) {
        FindCrvClosestPointFromS(crv, PosLoWorld(goal->pstep), &B_003DD020, 0, 0, 0, &goal->s, goal->sHint);
        goal->sHint = -1.0f;
    } else {
        FindCrvClosestPointAll(crv, PosLoWorld(goal->pstep), &B_003DD020, 0, 0, 0, &goal->s);
    }
    if (crv->closed != 0) {
        goal->open = 0;
        return;
    }
    goal->open = 1;
    if (goal->reverse != 0)
        goal->sEnd = SMinCrv(crv);
    else
        goal->sEnd = SMaxCrv(crv);
    GetPathPosFromS(crv, &goal->posEnd, 0, goal->sEnd);
}

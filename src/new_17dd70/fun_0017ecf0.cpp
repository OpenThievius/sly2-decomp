#include "sly2.h"
#include "goal.h"
#include "crv.h"
/* the curve as Advance reads it: its excluded ranges sit past CRV's declared bytes */
struct CRVRANGES : CRV {
    /* 0x180 */ void *ranges; /* reader: func_0017ECF0 (GoalFollowCurve's Advance) */
};
/* GoalFollowCurve (goals.h GOALFOLLOWCURVE) with the curve held as a pointer: the shared field is an s32 (guess) */
struct GOAL_17ECF0 : GOAL {
    CRVRANGES *crv;
    int fwd;
    float s;
    u8 unknown_0x3C[0x4];
    QW pos;
    u8 unknown_0x50[0x8];
    int param;
};
struct TARGET { int a[4]; QW pos; };
extern float D_FLT_002BE7BC;
extern float D_FLT_002BE7C0;
extern float D_FLT_002BE7C4;
extern "C" {
int FIsBasicDerivedFrom(void *, int);
float SMinCrv(CRVRANGES *);
float SMaxCrv(CRVRANGES *);
float SWrapCrv(CRVRANGES *, float);
void UpdateCrvExcludedRanges(void *);
float *PgFindCrvExcludedRange(void *, float);
void GetPathPosFromS(CRVRANGES *, QW *, void *, float);
void func_002562A8(TARGET *);
void SetGoalTarget(void *, TARGET *);
}
extern "C" void func_0017ECF0(GOAL_17ECF0 *pgoal, int force)
{
    float step;
    if (FIsBasicDerivedFrom(((void *)pgoal->pstep), 0x3A) != 0)
        step = D_FLT_002BE7BC;
    else
        step = D_FLT_002BE7C0;
    if (pgoal->fwd == 0)
        step = -step;
    float snew = pgoal->s + step;
    if (pgoal->crv->closed == 0) {
        float smin = SMinCrv(pgoal->crv);
        float smax = SMaxCrv(pgoal->crv);
        if (snew < smin)
            snew = smin;
        else if (snew > smax)
            snew = smax;
    } else {
        snew = SWrapCrv(pgoal->crv, snew);
    }
    if (pgoal->param == 0) {
        UpdateCrvExcludedRanges(pgoal->crv->ranges);
        float *range = PgFindCrvExcludedRange(pgoal->crv->ranges, snew);
        if (range != 0) {
            float edge;
            if (pgoal->fwd != 0)
                edge = range[1];
            else
                edge = range[0];
            snew = SWrapCrv(pgoal->crv, edge);
        }
    }
    if (force == 0) {
        float d = pgoal->s - snew;
        if (__builtin_fabsf(d) < D_FLT_002BE7C4)
            return;
    }
    pgoal->s = snew;
    GetPathPosFromS(pgoal->crv, &pgoal->pos, 0, snew);
    void *child = ((void *)pgoal->pgoalChild);
    TARGET t;
    func_002562A8(&t);
    t.pos = pgoal->pos;
    SetGoalTarget(child, &t);
}

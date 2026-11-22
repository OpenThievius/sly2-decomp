// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "vu0inline.h"
#include "stepguard.h"
#include "phys.h"
struct LINK { char pad[0x10]; void *zone; };
struct CRV { char pad[0xE8]; int count; char pad1[0xF4 - 0xEC]; QW *nodes; };
#include "goal.h"
struct GOAL_17C3E8 : GOAL {
    int state;
    char pad_34[0x3C];
    float dist;
};
extern "C" void func_001EEF98(GOAL_17C3E8 *);
extern "C" float GetAlertPan(ALERT *);
extern "C" QW PosLoWorld(void *);
extern "C" void DecomposeCylind(QW, float *, float *, float *);
extern "C" float RadNormalize__Ff(float);
extern "C" int FCheckLm__FP2LMf(void *, float);
extern "C" QW func_0017BFF8(GOAL_17C3E8 *, void *, QW, float);
extern "C" void FFindPathzoneCrv(void *, QW, QW, CRV *);
extern "C" void GoalFollowCrv_SetCrv(GOAL_17C3E8 *, CRV *, int);
extern "C" const float D_FLT_002BE748;
extern "C" void func_0017C3E8(GOAL_17C3E8 *goal)
{
    func_001EEF98(goal);
    if (goal->state == 0)
        return;
    STEPGUARD *jt = (STEPGUARD *)goal->pstep;
    CRV *crv = (CRV *)jt->pcrv;
    LINK *pz = 0;
    if (jt->pphys)
        pz = jt->pphys->plink;
    void *zone = 0;
    if (pz)
        zone = pz->zone;
    ALERT *alert = jt->palert;
    void *palo = alert->palo;
    float pan = GetAlertPan(alert);
    QW posAlert = PosLoWorld(palo);
    GOAL_17C3E8 *child = ((GOAL_17C3E8 *)goal->pgoalChild);
    float angles[2];
    if (D_FLT_002BE748 < child->dist)
        goto replan;
    {
        QW vec = VectorSub(crv->nodes[crv->count - 1], posAlert);
        DecomposeCylind(vec, &angles[0], &angles[1], 0);
        float offset = RadNormalize__Ff(angles[0] - pan);
        if (alert->radCone < __builtin_fabsf(offset))
            goto replan;
        if (FCheckLm__FP2LMf(((STEPGUARD *)goal->pstep)->lm, angles[1]))
            return;
    }
replan:
    QW posGuard = PosLoWorld(((STEPGUARD *)goal->pstep));
    QW posStand = func_0017BFF8(goal, zone, posAlert, pan);
    FFindPathzoneCrv(zone, posGuard, posStand, crv);
    GoalFollowCrv_SetCrv(child, crv, 0);
}

#include "sly2.h"
#include "vu0inline.h"
struct PZ { char pad[0x10]; void *zone; };
struct OWN { char pad0[0xDC]; PZ *pz; };
struct CRV { char pad[0xE8]; int count; char pad1[0xF4 - 0xEC]; QW *nodes; };
struct ALERT { char pad0[0xC]; void *palo; char pad1[0x18 - 0x10]; float radCone; };
struct JT { char pad0[0xE8]; OWN *own; char pad1[0x294 - 0xEC]; CRV *crv; char pad2[0x324 - 0x298]; char lm[4]; char pad3[0x3CC - 0x328]; ALERT *alert; };
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
    JT *jt = ((JT *)goal->pstep);
    CRV *crv = jt->crv;
    PZ *pz = 0;
    if (jt->own)
        pz = jt->own->pz;
    void *zone = 0;
    if (pz)
        zone = pz->zone;
    ALERT *alert = jt->alert;
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
        if (FCheckLm__FP2LMf(((JT *)goal->pstep)->lm, angles[1]))
            return;
    }
replan:
    QW posGuard = PosLoWorld(((JT *)goal->pstep));
    QW posStand = func_0017BFF8(goal, zone, posAlert, pan);
    FFindPathzoneCrv(zone, posGuard, posStand, crv);
    GoalFollowCrv_SetCrv(child, crv, 0);
}

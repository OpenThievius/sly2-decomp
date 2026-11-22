// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "step.h"
#include "phys.h"
struct LINK { char pad[0x10]; void *zone; };
struct CRV { char pad[0xE8]; int count; char pad1[0xF4 - 0xEC]; QW *nodes; };
#include "goal.h"
struct GOAL_144F48 : GOAL {
    int fSimple;
    char pad_34[0xC];
    QW posGoal;
};
extern "C" QW PosLoWorld(STEP *);
extern "C" void FFindPathzoneCrv(void *, QW, QW, CRV *);
extern "C" void MeasureCrv(CRV *);
extern "C" void GoalFollowCrv_SetCrv(GOAL_144F48 *, CRV *, int);

void GoalGotoPos_SetPos(GOAL_144F48 *goal, QW posGoal)
{
    goal->posGoal = posGoal;
    if (((GOAL_144F48 *)goal->pgoalChild) == 0)
        return;
    STEP *step = goal->pstep;
    CRV *crv = (CRV *)step->pcrv;
    LINK *pz = 0;
    if (step->pphys)
        pz = step->pphys->plink;
    void *zone = 0;
    if (pz)
        zone = pz->zone;
    QW posOwner = PosLoWorld(step);
    if (zone == 0 || goal->fSimple != 0) {
        crv->count = 2;
        QW *nodes = crv->nodes;
        nodes[0] = posOwner;
        crv->nodes[1] = goal->posGoal;
        MeasureCrv(crv);
    } else {
        FFindPathzoneCrv(zone, posOwner, goal->posGoal, crv);
    }
    GoalFollowCrv_SetCrv(((GOAL_144F48 *)goal->pgoalChild), crv, 0);
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "goalpost.h"
#include "clock.h"
#include "crv.h"
#include "ps2inline.h"
#include "vu0inline.h"
extern "C" {
float GRandInRange(float, float);
void Goal_Pop(GOAL **);
LO *func_00155A68(GOALPOSTWATCH *);
GOAL *func_00205438(STEPGUARD *, int);
QW PosLoWorld(void *);
float atan2f(float, float);
void func_00209818(GUARDHEADING *, float);
void func_0020AC28(STEPGUARD *, int, int, QW);
void GoalFollowCrv_SetCrv(GOALFOLLOWCRV *, CRV *, int);
void MeasureCrv(CRV *);
extern QW g_2a2dd0;
}

/* GoalPostWatch_SetState */
extern "C" void func_00155AE0(GOALPOSTWATCH *pgoal, int state)
{
    if (state == pgoal->state)
        return;
    switch (pgoal->state) {
    case 1:
        func_0020AC28(GOAL_GUARD(pgoal), 0, 0, g_2a2dd0);
        break;
    case 3:
        float base = g_2dded0.t;
        GOAL_GUARD(pgoal)->tCooldown = base + GRandInRange(pgoal->pnotice->low, pgoal->pnotice->high);
        pgoal->pnotice = 0;
        break;
    }
    Goal_Pop(&pgoal->pgoalChild);
    pgoal->state = state;
    pgoal->tState = g_2dded0.t;
    switch (state) {
    case 0: {
        pgoal->ploPost = func_00155A68(pgoal);
        GOALANIM *pturn = (GOALANIM *)func_00205438(GOAL_GUARD(pgoal), 0x9D);
        pturn->sgs = 0xB;
        QW first = PosLoWorld(pgoal->ploPost);
        QW second = PosLoWorld(GOAL_GUARD(pgoal));
        QW delta = VectorSub(first, second);
        float angle = atan2f(LaneX(RotateWords3(delta)), LaneX(delta)) + 3.1415927f;
        func_00209818(&GOAL_GUARD(pgoal)->heading, angle);
        pturn->Activate();
        pgoal->tLimit = 3.4028235e38f;
        break; }
    case 1: {
        GOALANIM *pwatch = (GOALANIM *)func_00205438(GOAL_GUARD(pgoal), 0x9E);
        pwatch->ptarget = pgoal->ploTarget;
        pwatch->Activate();
        break; }
    case 2: {
        GOALFOLLOWCRVANIM *pfollow = (GOALFOLLOWCRVANIM *)func_00205438(GOAL_GUARD(pgoal), 0xA7);
        CRV *pcrv = (CRV *)GOAL_GUARD(pgoal)->pcrv;
        pcrv->ccv = state;
        QW *first = pcrv->apos;
        *first = PosLoWorld(GOAL_GUARD(pgoal));
        QW *second = pcrv->apos;
        second[1] = PosLoWorld(pgoal->ploPost);
        MeasureCrv(pcrv);
        GoalFollowCrv_SetCrv(pfollow, pcrv, 0);
        pfollow->kind = 8;
        pfollow->ptarget = pgoal->ploTarget;
        pfollow->field_0x40 = 1;
        pfollow->Activate();
        break; }
    case 3: {
        GOALREACT *preact = (GOALREACT *)func_00205438(GOAL_GUARD(pgoal), 0xA4);
        preact->pxf = (XF *)pgoal->pnotice;
        preact->ptarget = pgoal->ploTarget;
        preact->Activate();
        GOAL_GUARD(pgoal)->tCooldown = 3.4028235e38f;
        pgoal->cReact = pgoal->cReact + 1;
        break; }
    }
}

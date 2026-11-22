// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "clock.h"
#include "crv.h"
#include "goalpatrol.h"
#include "sw.h"
extern "C" {
float GRandInRange(float, float);
void GoalFollowCrv_SetCrv(GOALFOLLOWCRV *, CRV *, int);
void Goal_Pop(GOAL **);
void MeasureCrv(CRV *);
QW PosLoWorld(LO *);
PO *PpoSwFocusBase(SW *);
void SetSoCnstrForce(SO *, int);
void SetSoCnstrTorque(SO *, int);
LO *func_0014AE18(GOALPATROL *);
GOAL *func_00205438(STEPGUARD *, int);
void func_0020AC28(STEPGUARD *, int, int, QW);
extern SW B_003DD490;
extern QW g_2a2dd0;
void func_0014AE38(GOALPATROL *pgoal, int stateNew) {
    int stateOld = pgoal->state;
    if (stateNew != stateOld) {
        switch (stateOld) {
        case 0:
            func_0020AC28(GOAL_GUARD(pgoal), 0, 0, g_2a2dd0);
            break;
        case 1:
        case -1:
            SetSoCnstrForce(GOAL_GUARD(pgoal), 1);
            SetSoCnstrTorque(GOAL_GUARD(pgoal), 1);
            break;
        case 3: {
            NOTICE *pnotice = pgoal->pnotice;
            float now = g_2dded0.t;
            GOAL_GUARD(pgoal)->tCooldown = now + GRandInRange(pnotice->low, pnotice->high);
            pgoal->pnotice = 0;
            break; }
        }
        Goal_Pop(&pgoal->pgoalChild);
        pgoal->state = stateNew;
        pgoal->tState = g_2dded0.t;
        switch (stateNew) {
        case 0: {
            GOALANIM *pwatch = (GOALANIM *)func_00205438(GOAL_GUARD(pgoal), 0x9E);
            pwatch->ptarget = PpoSwFocusBase(&B_003DD490);
            pwatch->Activate();
            {
                STEPGUARD *pguard = GOAL_GUARD(pgoal);
                pguard->Slot35(g_2a2dd0);
                pguard = GOAL_GUARD(pgoal);
                pguard->Slot36(g_2a2dd0);
                VECTOR *pvelGoal = (VECTOR *)&GOAL_GUARD(pgoal)->velGoal;
                pvelGoal->z = 0.0f;
                pvelGoal->y = 0.0f;
                pvelGoal->x = 0.0f;
            }
            return; }
        case 1: {
            CRV *pcrv = (CRV *)GOAL_GUARD(pgoal)->pcrv;
            pcrv->ccv = 2;
            QW *first = pcrv->apos;
            *first = PosLoWorld(GOAL_GUARD(pgoal));
            QW *second = pcrv->apos;
            second[1] = PosLoWorld(func_0014AE18(pgoal));
            MeasureCrv(pcrv);
            GOALFOLLOWCRVANIM *pfollow = (GOALFOLLOWCRVANIM *)func_00205438(GOAL_GUARD(pgoal), 0xA7);
            GoalFollowCrv_SetCrv(pfollow, pcrv, 0);
            pfollow->field_0x64 = 25.0f;
            pfollow->kind = 8;
            pfollow->field_0x40 = 1;
            pfollow->ptarget = PpoSwFocusBase(&B_003DD490);
            pfollow->Activate();
            GOAL_GUARD(pgoal)->tCooldown = g_2dded0.t;
            SetSoCnstrForce(GOAL_GUARD(pgoal), 0);
            SetSoCnstrTorque(GOAL_GUARD(pgoal), 0);
            return; }
        case 2: {
            GOALJUMP *pjump = (GOALJUMP *)func_00205438(GOAL_GUARD(pgoal), 0xAC);
            pjump->posTarget = PosLoWorld(func_0014AE18(pgoal));
            pjump->fTrackTarget = 1;
            pjump->Activate();
            return; }
        case 3: {
            GOALREACT *preact = (GOALREACT *)func_00205438(GOAL_GUARD(pgoal), 0xA4);
            preact->ptarget = (LO *)GOAL_GUARD(pgoal)->pbasicAlert;
            preact->pxf = (XF *)pgoal->pnotice;
            preact->Activate();
            GOAL_GUARD(pgoal)->tCooldown = 3.4028235e38f;
            return; }
        case 4: {
            GOALANIM *pwatch = (GOALANIM *)func_00205438(GOAL_GUARD(pgoal), 0x9E);
            pwatch->ptarget = PpoSwFocusBase(&B_003DD490);
            pwatch->sgs = 1;
            pwatch->Activate();
            return; }
        case -1:
            SetSoCnstrForce(GOAL_GUARD(pgoal), 0);
            SetSoCnstrTorque(GOAL_GUARD(pgoal), 0);
            break;
        }
    }
}
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "goals.h"
#include "clock.h"
#include "po.h"

struct STEP;

extern "C" {
void Goal_Pop(GOAL **ppgoal);
void WarpJtToPoint(STEP *pjt, QW pos);
GOAL *func_00205438(STEP *pstep, int type);
int FIsBasicDerivedFrom(LO *plo, int index);
float GRandInRange(float min, float max);
void func_001457A8(GOALPARTNERFOLLOW *pgoal);
int CidGetBasic(STEP *pstep);
}

extern "C" void func_00145B18(GOALPARTNERFOLLOW *pgoal, int state)
{
    if (state == pgoal->state)
        return;
    Goal_Pop(&pgoal->pgoalChild);
    pgoal->state = state;
    pgoal->tState = g_2dded0.t;
    switch (state) {
    case 0: {
        GOALFOLLOWCRVVJOY *pgoalLook = (GOALFOLLOWCRVVJOY *)func_00205438(pgoal->pstep, 0xA8);
        if (FIsBasicDerivedFrom(pgoal->ploLeader, 0x32) != 0) {
            pgoalLook->pjoy = ((PO *)pgoal->ploLeader)->pjoy;
            pgoalLook->kind = 8;
            pgoalLook->tDelay = GRandInRange(0.1f, 0.3f);
        }
        func_001457A8(pgoal);
        pgoalLook->Activate();
        break;
    }
    case 1:
        WarpJtToPoint(pgoal->pstep, pgoal->posWarp);
        break;
    case 2: {
        int cid = CidGetBasic(pgoal->pstep);
        switch (cid) {
        case 0x36: {
            GOALPARTNERATTACK *pgoalAttack = (GOALPARTNERATTACK *)func_00205438(pgoal->pstep, 0xC3);
            pgoalAttack->ploTarget = pgoal->ploTarget;
            pgoalAttack->Activate();
            break;
        }
        case 0x37: {
            GOALPARTNERATTACK *pgoalAttack = (GOALPARTNERATTACK *)func_00205438(pgoal->pstep, 0xC4);
            pgoalAttack->ploTarget = pgoal->ploTarget;
            pgoalAttack->Activate();
            break;
        }
        case 0x35: {
            GOALPARTNERATTACK *pgoalAttack = (GOALPARTNERATTACK *)func_00205438(pgoal->pstep, 0xC5);
            pgoalAttack->ploTarget = pgoal->ploTarget;
            pgoalAttack->Activate();
            break;
        }
        }
        break;
    }
    }
}

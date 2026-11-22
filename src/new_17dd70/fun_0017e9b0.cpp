// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "vu0inline.h"
#include "stepguard.h"
#include "goals.h"
/* the part of STEP this reads at 0x240 (a quadword: TranslateToPos is given the point minus it; JT and func_00155D90 read it the same
   way, and step.h declares floats around it: a local view until they agree) */
struct STEPOFFSETVIEW {
    u8 unknown_0x0[0x240];
    QW posOffset;
};
extern "C" {
void Goal_Pop(GOAL **);
QW PosLoWorld(STEP *);
QW func_001C1EC0(GOALTARGET *, QW);
int FFindSurfaceAlongUp(QW *, int, int, float, float);
int func_0017D608(QW *);
GOAL *func_00205438(STEP *, int);
void ClearGuardPathMode(STEPGUARD *);
extern QW g_2a2dd0;
}
extern "C" void func_0017E9B0(GOALSNAPTOPOINT *pgoal)
{
    QW pos;
    Goal_Pop(&pgoal->pgoalChild);
    pos = func_001C1EC0(&pgoal->target, PosLoWorld(pgoal->pstep));
    if (!FFindSurfaceAlongUp(&pos, 1, 0, 150.0f, -250.0f))
        func_0017D608(&pos);
    if (((STEPGUARD *)pgoal->pstep)->grf & 1) {
        GOALJUMP *pmove = (GOALJUMP *)func_00205438(pgoal->pstep, 0xAC);
        pmove->posTarget = pos;
        pmove->fTrackTarget = 1;
        pmove->Activate();
    } else {
        ClearGuardPathMode((STEPGUARD *)pgoal->pstep);
        pos = VectorSub(pos, ((STEPOFFSETVIEW *)pgoal->pstep)->posOffset);
        pgoal->pstep->TranslateToPos(pos);
        pgoal->pstep->Slot35(g_2a2dd0);
        pgoal->pstep->Slot36(g_2a2dd0);
    }
}

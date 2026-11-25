// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jt.h"
#include "xf.h"
#include "so.h"
#include "act.h"
#include "stepguard.h"
#include "goals.h"
/* the 0x30-byte lead the player's goals pass (JT::PredictLead); only its kind is read here (0: nothing found) */
struct LEAD {
    s32 kind;
    u8 unknown_0x4[0x2C];
};
/* GoalGrab (goals.h GOALGRAB) with the actuator of 0x64, which only this function reads: a view of the class past GOALANIM */
struct GOAL_17ABC8 : GOALANIM {
    u8 unknown_0x50[0xC];
    /* 0x5C */ JT *ptarget;
    /* 0x60 */ int fHeld;
    /* 0x64 */ ACTVAL *pact;
};
extern "C" float g_2dded0;
extern "C" void func_0017AA78(GOAL_17ABC8 *, LEAD *, QW *, QW *);
extern "C" QW ConvertXfPos(int, XF *, QW);
extern "C" QW ConvertXfVec(int, XF *, QW);
extern "C" void SetActvalGoal(ACTVAL *, QW, QW);
void func_0017ABC8(GOAL_17ABC8 *pgoal)
{
    LEAD query;
    QW posAim, vecAim;
    if (pgoal->fHeld == 0)
        return;
    pgoal->ptarget->PredictLead(&query, pgoal->pact->tGoal - g_2dded0);
    if (query.kind == 0) {
        pgoal->fHeld = 0;
        return;
    }
    XF *xf = ((SO *)pgoal->pstep)->pxfLinear;
    func_0017AA78(pgoal, &query, &posAim, &vecAim);
    QW pos = ConvertXfPos(0, xf->pxfParent, posAim);
    QW vec = ConvertXfVec(0, xf->pxfParent, vecAim);
    SetActvalGoal(pgoal->pact, pos, vec);
}

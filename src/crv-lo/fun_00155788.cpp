// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "clock.h"
#include "goalpost.h"
/* class 0xB5, the goal GoalPostRun pushes in state 0: it runs to the post and watches the target */
struct GOALPOSTGO : GOAL {
    u8 unknown_0x30[0x8];
    /* 0x38 */ POSTPAIR *ppost;
    u8 unknown_0x3C[0x10];
    /* 0x4C */ LO *ptarget;
};
extern "C" {
void Goal_Pop(GOAL **);
GOAL *func_00205438(STEPGUARD *, int);
}

/* GoalPostRun_SetState */
extern "C" void func_00155788(GOALPOSTRUN *pgoal, int state)
{
    if (state == pgoal->state)
        return;
    if (pgoal->state == 0)
        pgoal->ppost->used = 1;
    Goal_Pop(&pgoal->pgoalChild);
    pgoal->state = state;
    pgoal->tState = g_2dded0.t;
    switch (state) {
    case 0: {
        GOALPOSTGO *ppostgo = (GOALPOSTGO *)func_00205438((STEPGUARD *)pgoal->pstep, 0xB5);
        ppostgo->ppost = pgoal->ppost;
        ppostgo->ptarget = pgoal->ptarget;
        ppostgo->Activate();
        ((STEPGUARDPOSTS *)pgoal->pstep)->tickPick = ((STEPGUARD *)pgoal->pstep)->field_0x33C;
        break; }
    case 1: {
        GOALNOTICE *pnotice = (GOALNOTICE *)func_00205438((STEPGUARD *)pgoal->pstep, 0xA5);
        LO *ptarget = pgoal->ptarget;
        pnotice->field_0x40 = state;
        pnotice->ptarget = ptarget;
        pnotice->Activate();
        break; }
    }
}

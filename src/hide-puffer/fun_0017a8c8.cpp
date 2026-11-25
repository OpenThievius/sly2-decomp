// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
struct GOAL_17A8C8 : GOAL {
    int state;
    float tState;
};
struct B8 { char b[8]; };
struct KT { union { struct { B8 a; B8 b; int c; }; int sgs[5]; }; };
extern "C" const KT RO_002A55A0;
struct CLOCK { float t; float dt; };
extern "C" CLOCK g_2dded0;
extern "C" void Goal_Pop(void *);
extern "C" void func_001EF038(GOAL_17A8C8 *);
extern "C" GOALANIM *func_00205438(STEPGUARD *, int);
void func_0017A8C8(GOAL_17A8C8 *pgoal, int nState)
{
    if (pgoal->state == nState)
        return;
    Goal_Pop(&pgoal->pgoalChild);
    pgoal->state = nState;
    pgoal->tState = g_2dded0.t;
    if (nState != -1) {
        if (nState > -2) {
            if (nState < 5) {
                GOALANIM *pobj = func_00205438(((STEPGUARD *)pgoal->pstep), 0x9D);
                KT kinds = RO_002A55A0;
                pobj->sgs = kinds.sgs[pgoal->state];
                pobj->Activate();
                ((STEPGUARD *)pgoal->pstep)->fDown = (unsigned)pgoal->state < 2;
            }
        }
    } else {
        func_001EF038(pgoal);
        ((STEPGUARD *)pgoal->pstep)->fDown = 0;
    }
}

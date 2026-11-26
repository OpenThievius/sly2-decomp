#include "sly2.h"
#include "goals.h"
#include "stepguard.h"
#include "sma.h"
extern "C" float g_2dded0;
extern "C" float GRandInRange(float, float);
extern "C" void SetSmaGoal__FP3SMA3OID(SMA *, int);
extern "C" void GoalFlinch_SetState(GOALFLINCH *goal, int state)
{
    if (state == goal->stateFlinch)
        return;
    goal->stateFlinch = state;
    goal->stateF = (float)state;
    switch (state) {
    case 0: {
        if (goal->panimref->kind == 1)
            SetSmaGoal__FP3SMA3OID((SMA *)goal->panimref->pinst, 0x44);
        float base = g_2dded0;
        STEPGUARD *guard = (STEPGUARD *)goal->pstep;
        goal->tNext = base + GRandInRange(guard->field_0xE7C, guard->field_0xE80);
        break;
    }
    case 1:
        if (goal->panimref->kind == state)
            SetSmaGoal__FP3SMA3OID((SMA *)goal->panimref->pinst, 0x43);
        break;
    }
}

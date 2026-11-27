#include "sly2.h"
extern "C" void GoalAnim_Update(void*);
extern "C" QW PosLoWorld(void*);
extern "C" float g_2dded0;
#include "stepguard.h"
#include "goals.h"
#include "hitfx.h"
extern "C" void GoalFlinch_SetState(GOALFLINCH*, int);
extern "C" void func_0017A670(GOALFLINCH* goal)
{
    GoalAnim_Update(goal);
    int state;
    do {
        state = goal->stateFlinch;
        if (state == 0 && g_2dded0 > goal->tNext) {
            GoalFlinch_SetState(goal, 1);
        }
    } while (goal->stateFlinch != state);
    STEPGUARD* guard = (STEPGUARD*)goal->pstep;
    HITFX* effect = guard->phitfx;
    effect->pos = PosLoWorld(guard);
}

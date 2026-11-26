#include "sly2.h"
extern "C" void GoalAnim_Update(void*);
extern "C" QW PosLoWorld(void*);
extern "C" float g_2dded0;
#include "stepguard.h"
#include "goals.h"
/* the effect the guard keeps at STEPGUARD 0x35C: func_0017A670 stores the guard position at its 0x20 (one reader: a local view of hitfx.h's HITFX) */
struct HITFXPOS {
    u8 unknown_0x0[0x20];
    /* 0x20 */ QW pos;
};
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
    HITFXPOS* effect = (HITFXPOS*)guard->field_0x35C;
    effect->pos = PosLoWorld(guard);
}

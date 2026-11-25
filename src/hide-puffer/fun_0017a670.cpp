#include "sly2.h"
extern "C" void GoalAnim_Update(void*);
extern "C" void GoalFlinch_SetState(void*, int);
extern "C" QW PosLoWorld(void*);
extern "C" float g_2dded0;
struct Track { u8 unknown_0x0[0x20]; QW pos; };
struct Guard { u8 unknown_0x0[0x35C]; Track* track; };
#include "goal.h"
struct GOAL_17A670 : GOAL {
    u8 unknown_0x30[0x20];
    int state;
    u8 unknown_0x54[0x4];
    float tNext;
};
extern "C" void func_0017A670(GOAL_17A670* goal)
{
    GoalAnim_Update(goal);
    int state;
    do {
        state = goal->state;
        if (state == 0 && g_2dded0 > goal->tNext) {
            GoalFlinch_SetState(goal, 1);
        }
    } while (goal->state != state);
    Guard* guard = ((Guard*)goal->pstep);
    Track* track = guard->track;
    track->pos = PosLoWorld(guard);
}

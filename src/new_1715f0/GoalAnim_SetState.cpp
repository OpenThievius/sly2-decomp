// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct AnimSource {
    u8 unknown_0x0[0x74];
    f32 length;
};

struct AnimTimes {
    u8 unknown_0x0[0x1C];
    f32 elapsed;
};

struct Animref {
    s32 started;
    AnimSource *source;
    AnimTimes *times;
    s32 flags;
};

struct GoalActor {
    u8 unknown_0x0[0x1A4];
    s32 pendingState;
    u8 unknown_0x1A8[0xFD0 - 0x1A8];
    char animList[0x20];
    char savedRate[8];
};

struct GoalAnim {
    u8 unknown_0x0[0x10];
    GoalActor *actor;
    u8 unknown_0x14[0x30 - 0x14];
    s32 state;
    f32 stateTime;
    u8 unknown_0x38[0x40 - 0x38];
    Animref *animref;
};

static inline f32 *SavedRate(GoalActor *actor)
{
    return (f32 *)actor->savedRate;
}

extern "C" {
s32 FIsGuardInSgs(GoalActor *, s32);
void StartAnimref(Animref *, GoalActor *, s32, f32);
void StopAnimref(Animref *);
void func_001EF038(GoalAnim *);
void func_00209788(void *, GoalAnim *);
void func_00209790(void *, GoalAnim *);
extern f32 g_2dded0;

void GoalAnim_SetState(GoalAnim *goal, s32 state)
{
    if (goal->state != state) {
        goal->state = state;
        goal->stateTime = g_2dded0;
        switch (state) {
        case 0: {
            func_00209788(goal->actor->animList, goal);
            Animref *animref = goal->animref;
            f32 rate;
            if (animref->started == 0 && FIsGuardInSgs(goal->actor, 9) != 0 && g_2dded0 == SavedRate(goal->actor)[1]) {
                rate = goal->animref->source->length * SavedRate(goal->actor)[0];
            } else {
                rate = 0.0f;
            }
            StartAnimref(goal->animref, goal->actor, goal->animref->flags | 1, rate);
            return;
        }
        case 1:
            func_001EF038(goal);
            if (goal->animref != 0) {
                if (goal->animref->started == 0 && FIsGuardInSgs(goal->actor, 9) != 0) {
                    Animref *animref = goal->animref;
                    SavedRate(goal->actor)[0] = animref->times->elapsed / animref->source->length;
                    SavedRate(goal->actor)[1] = g_2dded0;
                }
                StopAnimref(goal->animref);
                goal->animref = 0;
                func_00209790(goal->actor->animList, goal);
            }
            goal->actor->pendingState = 0;
            break;
        }
    }
}
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "stepguard.h"
#include "goals.h"

/* ANIMREF (guard.h) has no view of its source and times: the two words below are read only by this function */
struct AnimSource {
    u8 unknown_0x0[0x74];
    f32 length;
};

struct AnimTimes {
    u8 unknown_0x0[0x1C];
    f32 elapsed;
};

/* the pair the animation's progress is saved in when a goal stops: STEPGUARD's 0xFF0 (a gap in stepguard.h, only this function
   reads it) and field_0xFF4 (OnGuardRemove clears it) */
static inline f32 *SavedRate(STEPGUARD *actor)
{
    return (f32 *)((char *)actor + 0xFF0);
}

extern "C" {
s32 FIsGuardInSgs(STEPGUARD *, s32);
void StartAnimref(ANIMREF *, STEPGUARD *, s32, f32);
void StopAnimref(ANIMREF *);
void func_001EF038(GOALANIM *);
void func_00209788(void *, GOALANIM *);
void func_00209790(void *, GOALANIM *);
}
extern f32 g_2dded0;

extern "C" void GoalAnim_SetState(GOALANIM *goal, s32 state)
{
    if (goal->state != state) {
        goal->state = state;
        goal->tState = g_2dded0;
        switch (state) {
        case 0: {
            func_00209788(&((STEPGUARD *)goal->pstep)->heading, goal);
            ANIMREF *animref = goal->panimref;
            f32 rate;
            if (animref->kind == 0 && FIsGuardInSgs(((STEPGUARD *)goal->pstep), 9) != 0 && g_2dded0 == SavedRate(((STEPGUARD *)goal->pstep))[1]) {
                rate = ((AnimSource *)goal->panimref->pdata)->length * SavedRate(((STEPGUARD *)goal->pstep))[0];
            } else {
                rate = 0.0f;
            }
            StartAnimref(goal->panimref, ((STEPGUARD *)goal->pstep), goal->panimref->grf | 1, rate);
            return;
        }
        case 1:
            func_001EF038(goal);
            if (goal->panimref != 0) {
                if (goal->panimref->kind == 0 && FIsGuardInSgs(((STEPGUARD *)goal->pstep), 9) != 0) {
                    ANIMREF *animref = goal->panimref;
                    SavedRate(((STEPGUARD *)goal->pstep))[0] = ((AnimTimes *)animref->pinst)->elapsed / ((AnimSource *)animref->pdata)->length;
                    SavedRate(((STEPGUARD *)goal->pstep))[1] = g_2dded0;
                }
                StopAnimref(goal->panimref);
                goal->panimref = 0;
                func_00209790(&((STEPGUARD *)goal->pstep)->heading, goal);
            }
            ((STEPGUARD *)goal->pstep)->fLock = 0;
            break;
        }
    }
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "goals.h"
#include "step.h"
#include "sly2.h"
/* the actor the goal steers (a STEP subclass, 0x35C past STEP's size): not LO */
struct ACTOR : STEP { u8 unknown_0x2C0[0x35C - 0x2C0]; char *p35C; };
struct CMOBJ;
extern float g_2dded0;
extern CMOBJ B_002DDF40;
void GoalAnim_Update(GOAL *);
QW PosLoWorld(LO *);
void JoltCm(CMOBJ *, int);
void func_001F7A68(LO *, int);
void GoalHit_Update(GOALHIT *goal)
{
    GoalAnim_Update(goal);
    ACTOR *lo = (ACTOR *)goal->pstep;
    char *target = lo->p35C;
    /* a typed QW member store makes gcc move the g_2dded0 load before the store (score 7): the cast stays */
    *(QW *)(target + 0x20) = PosLoWorld(lo);
    float limit = g_2dded0 + 0.0001f;
    if (goal->tJolt < limit) {
        goal->tJolt = 3.402823466e+38f;
        JoltCm(&B_002DDF40, 0);
    }
    if (goal->tLimit < limit) {
        goal->tLimit = 3.402823466e+38f;
        func_001F7A68((ACTOR *)goal->pstep, 2);
    }
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "goals.h"
#include "step.h"
#include "sly2.h"
#include "stepguard.h"
#include "hitfx.h"
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
    STEPGUARD *lo = (STEPGUARD *)goal->pstep;
    HITFX *target = lo->phitfx;
    /* through a QW pointer: a direct member store makes gcc move the g_2dded0 load before the store (score 7) */
    QW *ppos = &target->pos;
    *ppos = PosLoWorld(lo);
    float limit = g_2dded0 + 0.0001f;
    if (goal->tJolt < limit) {
        goal->tJolt = 3.402823466e+38f;
        JoltCm(&B_002DDF40, 0);
    }
    if (goal->tLimit < limit) {
        goal->tLimit = 3.402823466e+38f;
        func_001F7A68((STEPGUARD *)goal->pstep, 2);
    }
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"

extern "C" void func_00174B28(GOALHIT *);
extern "C" void ReplaceSwHitFx(char *, int, s128, int, int);
extern "C" char B_003DD490[];
extern "C" s128 g_2a2dd0;

extern "C" void GoalHit_Deactivate(GOALHIT *goalHit)
{
    func_00174B28(goalHit);
    ReplaceSwHitFx(B_003DD490, -1, g_2a2dd0, 0, (int)&GOAL_GUARD(goalHit)->phitfx);
}

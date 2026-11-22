// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"

/* the three words of STEP::velGoal (step.h, a QW) that func_00209790 clears one by one */
struct STEPVELGOALWORDS {
    u8 unknown_0x0[0x190];
    s32 velGoalWord[3];
};

extern "C" void func_001F5078(STEP *);
void func_00209790(GUARDHEADING *pheading)
{
    pheading->field_0x0 = 0;
    STEPVELGOALWORDS *pstep = (STEPVELGOALWORDS *)pheading->pstep;
    pheading->fHold = 0;
    s32 *word = pstep->velGoalWord;
    word[2] = 0;
    word[1] = 0;
    word[0] = 0;
    func_001F5078(pheading->pstep);
}

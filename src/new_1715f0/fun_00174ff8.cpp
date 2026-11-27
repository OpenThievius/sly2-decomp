// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goal.h"
struct GOAL_174FF8 : GOAL {
    u8 unknown_0x30[0x8];
    int aim;
};
extern "C" QW g_2a2dd0;
extern "C" void func_00174950(GOAL_174FF8 *);
extern "C" int FIsGuardInSgs(STEPGUARD *, int);
extern "C" void func_0020AB68(STEPGUARD *, int, int, QW);
extern "C" void ResetSensorStates(SENSOR *);
extern "C" void SetXfKind(STEPGUARD *, XF *, int);
void func_00174FF8(GOAL_174FF8 *goal)
{
    func_00174950(goal);
    if (FIsGuardInSgs(((STEPGUARD *)goal->pstep), 1)) {
        func_0020AB68(((STEPGUARD *)goal->pstep), 0, 0, g_2a2dd0);
        ResetSensorStates(((STEPGUARD *)goal->pstep)->psensor);
        int aim = ((STEPGUARD *)goal->pstep)->field_0xFCC;
        if (aim != 0) goal->aim = aim;
    }
    SetXfKind(((STEPGUARD *)goal->pstep), ((STEPGUARD *)goal->pstep)->pxfLinear, 1);
    if (goal->aim == 0) {
        SetXfKind(((STEPGUARD *)goal->pstep), ((STEPGUARD *)goal->pstep)->pxfAngular, 1);
    }
}

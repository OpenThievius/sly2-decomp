// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goal.h"
/* the goal: only its word at 0x40 is read here (one reader: a local view) */
struct GOAL_176060 : GOAL { u8 unknown_0x30[0x10]; int busy; };
extern "C" int func_0020A7E0(ALERT *);
int func_00176060(GOAL_176060 *obj)
{
    int result;
    if (obj->busy) {
        result = 0;
    } else {
        STEPGUARD *parent = (STEPGUARD *)obj->pstep;
        if (parent->field_0x3D4)
            result = 0;
        else
            result = func_0020A7E0(parent->palert);
    }
    return result;
}

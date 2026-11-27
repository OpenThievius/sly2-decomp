// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goal.h"
extern "C" void func_00174B28(GOAL *);
void func_001752C0(GOAL *obj)
{
    func_00174B28(obj);
    ((STEPGUARD *)obj->pstep)->fFlag = 0;
}

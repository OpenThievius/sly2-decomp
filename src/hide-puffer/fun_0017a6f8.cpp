// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" void func_001EEF68(GOAL *);
extern "C" void AddGuardSgs(STEPGUARD *, int);
void func_0017A6F8(GOALB0 *pgoal)
{
    func_001EEF68(pgoal);
    AddGuardSgs((STEPGUARD *)pgoal->pstep, 0x16);
    pgoal->state = -1;
}

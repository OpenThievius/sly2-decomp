// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" void func_001EEF68(GOAL *);
void func_0017B590(GOALSTAND *pgoal)
{
    func_001EEF68(pgoal);
    pgoal->state = -1;
}

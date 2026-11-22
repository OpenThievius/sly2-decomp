// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" void func_00174920(GOALANIM *);
void func_00179750(GOALANIM *pgoal)
{
    func_00174920(pgoal);
    pgoal->sgs = 6;
}

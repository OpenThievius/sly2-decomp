// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" void func_00174920(GOALANIM *);
void func_0017A9D0(GOALGRAB *pgoal)
{
    func_00174920(pgoal);
    pgoal->sgs = 0x17;
    pgoal->phase = -1;
}

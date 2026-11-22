// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" void func_00174920(GOALANIM *);
void func_0017A4B0(GOALFLINCH *pgoal)
{
    func_00174920(pgoal);
    pgoal->sgs = 0x10;
    pgoal->stateFlinch = -1;
}

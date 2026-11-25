// SPDX-License-Identifier: GPL-3.0-or-later
#include "tank.h"
extern LM D_002C4400;
extern "C" void InitPo(TANK *);
void InitTank(TANK *t)
{
    InitPo(t);
    t->lmSkill = D_002C4400;
    t->skill = t->lmSkill.gMax;
    t->lmPan.gMin = -1.5f;
    t->lmPan.gMax = 1.5f;
    t->lmTilt.gMin = -0.7f;
    t->lmTilt.gMax = 0.7f;
    t->fRotAct = 1;
    t->field_0x1D4 = 1;
    t->field_0x1D0 = t;
}

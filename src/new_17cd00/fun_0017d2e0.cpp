/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
extern "C" void func_001EEF70(GOAL *);
extern "C" GOAL *func_00205438(STEPGUARD *, int);
extern "C" void func_0017D2E0(GOAL *pgoal) {
    func_001EEF70(pgoal);
    GOALANIM *panim = (GOALANIM *)func_00205438(GOAL_GUARD(pgoal), 0x9D);
    panim->sgs = 2;
    panim->Activate();
}

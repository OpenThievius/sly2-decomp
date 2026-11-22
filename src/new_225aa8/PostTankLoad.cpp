// SPDX-License-Identifier: GPL-3.0-or-later
#include "tank.h"

extern "C" {
void PostSoLoad(SO *pso);
void func_00226370(TANK *ptank, int fRotAct);

void PostTankLoad(TANK *ptank) {
    PostSoLoad(ptank);
    if (ptank->fRotAct != 0) {
        ptank->fRotAct = 0;
        func_00226370(ptank, 1);
    }
}
}

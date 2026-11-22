// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"

extern "C" {
void WakeXf(SO *, XF *);

void func_001F5078(SO *pso) {
    if (pso->poxa != 0) {
        pso->SetGrfField(4);
        if (pso->pphys != 0) {
            WakeXf(pso, pso->pxfLinear);
            WakeXf(pso, pso->pxfAngular);
        }
    }
}
}

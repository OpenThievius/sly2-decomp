// SPDX-License-Identifier: GPL-3.0-or-later
#include "tank.h"
#include "cm.h"


void SetCmPolicy(CM *pcm, CPP cpp, CPLCY *pcplcy, SO *pso, void *pv);
void RevokeCmPolicy(CM *pcm, int grf, CPP cpp, CPLCY *pcplcy, SO *pso, void *pv);

extern "C" {
void OnPoActive(PO *ppo, int fActive);

void OnTankActive(TANK *ptank, int fActive) {
    OnPoActive(ptank, fActive);
    if (fActive != 0) {
        SetCmPolicy(&B_002DDF40, CPP_TANK, &B_002DDF40.cpattach, ptank, 0);
        return;
    }
    RevokeCmPolicy(&B_002DDF40, 0xF, CPP_TANK, &B_002DDF40.cpattach, ptank, 0);
}
}

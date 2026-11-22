// SPDX-License-Identifier: GPL-3.0-or-later
#include "tank.h"
#include "cm.h"

/* B_002DDF40's policy slot past acplcy[2] (CM, include/cm.h, stops there): a local view, read here only */
struct CMTANKVIEW : CM {
    CPLCY cplcyTank;
};

void SetCmPolicy(CM *pcm, CPP cpp, CPLCY *pcplcy, SO *pso, void *pv);
void RevokeCmPolicy(CM *pcm, int grf, CPP cpp, CPLCY *pcplcy, SO *pso, void *pv);

extern "C" {
void OnPoActive(PO *ppo, int fActive);

void OnTankActive(TANK *ptank, int fActive) {
    OnPoActive(ptank, fActive);
    if (fActive != 0) {
        SetCmPolicy(&B_002DDF40, CPP_TANK, &((CMTANKVIEW *)&B_002DDF40)->cplcyTank, ptank, 0);
        return;
    }
    RevokeCmPolicy(&B_002DDF40, 0xF, CPP_TANK, &((CMTANKVIEW *)&B_002DDF40)->cplcyTank, ptank, 0);
}
}

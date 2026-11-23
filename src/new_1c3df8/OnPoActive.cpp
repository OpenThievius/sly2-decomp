// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "po.h"
#include "cm.h"
extern "C" void SetTnTnsOverride(TN *, int);
void SetCmPolicy(CM *, CPP, CPLCY *, SO *, void *);
void RevokeCmPolicy(CM *, int, CPP, CPLCY *, SO *, void *);
void OnPoActive(PO *ppo, int fActive)
{
    if (fActive != 0) {
        if (ppo->ptn != 0) {
            SetTnTnsOverride(ppo->ptn, 1);
        } else {
            SetCmPolicy(&B_002DDF40, CPP_DEFAULT, &B_002DDF40.cptn, ppo, 0);
        }
    } else {
        if (ppo->ptn != 0) {
            SetTnTnsOverride(ppo->ptn, 0);
        } else {
            RevokeCmPolicy(&B_002DDF40, 0xf, CPP_DEFAULT, &B_002DDF40.cptn, ppo, 0);
        }
    }
}

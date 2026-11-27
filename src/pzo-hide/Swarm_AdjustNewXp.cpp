// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"
#include "xp.h"

extern "C" {
s32 FIsBasicDerivedFrom(void *, s32);
void func_0017F1A0(SWARM *, XP *, s32);
void func_0017F5B0(SWARM *, void *);

void Swarm_AdjustNewXp(SWARM *swarm, XP *pxp, s32 iside)
{
    void *plo;

    func_0017F1A0(swarm, pxp, iside);
    if (swarm->dhp != 0) {
        plo = pxp->axpd[1 - iside].pso;
        if (FIsBasicDerivedFrom(plo, 0x47) != 0) {
            func_0017F5B0(swarm, plo);
        }
    }
}
}

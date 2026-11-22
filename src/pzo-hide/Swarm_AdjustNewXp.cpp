// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

/* the contact record of a new touch: one XPSIDE per party, 0x40 bytes each (the same layout AdjustLootNewXp and AdjustMurrayNewXp read) */
struct XPSIDE {
    u8 unknown_0x0[0xC];
    /* 0xC */ void *plo; /* the object on this side */
    u8 unknown_0x10[0x30];
};
struct XP {
    XPSIDE side[2];
};

extern "C" {
s32 FIsBasicDerivedFrom(void *, s32);
void func_0017F1A0(SWARM *, XP *, s32);
void func_0017F5B0(SWARM *, void *);

void Swarm_AdjustNewXp(SWARM *swarm, XP *pxp, s32 iside)
{
    void *plo;

    func_0017F1A0(swarm, pxp, iside);
    if (swarm->dhp != 0) {
        plo = pxp->side[1 - iside].plo;
        if (FIsBasicDerivedFrom(plo, 0x47) != 0) {
            func_0017F5B0(swarm, plo);
        }
    }
}
}

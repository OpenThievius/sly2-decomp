// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "loot.h"
#include "xp.h"
struct UL { u64 v; } __attribute__((packed));
extern "C" char B_003DD490[];
extern "C" const UL RO_002A4B58;
void func_001F4FB0(SO *, XP *, int);
int FIsBasicDerivedFrom(void *, int);
void QueueSwCallbackOnce(void *, SO *, u64, int);
void AdjustLootNewXp(LOOT *ploot, XP *pxp, int iside)
{
    func_001F4FB0(ploot, pxp, iside);
    if (ploot->state == 5) {
        if (!FIsBasicDerivedFrom(pxp->axpd[1 - iside].psoRoot, 0x34))
            QueueSwCallbackOnce(B_003DD490, ploot, RO_002A4B58.v, 0);
    }
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "sohit.h"
#include "xp.h"

extern "C" {
void func_0017F1A0(SOHIT *);
void func_0017F5B0(SOHIT *, void *);
extern SO *g_2dfb80; /* the mount (Mount_Init stores a MOUNT there) */

void Chaser_AdjustNewXp(SOHIT *chaser, XP *pxp, s32 iside) {
    SO *other;

    func_0017F1A0(chaser);
    if (chaser->dhp != 0) {
        other = pxp->axpd[1 - iside].psoRoot;
        if (other == g_2dfb80) {
            func_0017F5B0(chaser, other);
        }
    }
}
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "sohit.h"

/* the contact record of a new touch: one XPSIDE per party, 0x40 bytes each (Swarm_AdjustNewXp reads the same layout) */
struct XPSIDE {
    u8 unknown_0x0[0x8];
    /* 0x8 */ s32 field_0x8; /* compared with g_2dfb80 */
    u8 unknown_0xC[0x34];
};
struct XP {
    XPSIDE side[2];
};

extern "C" {
void func_0017F1A0(SOHIT *);
void func_0017F5B0(SOHIT *, void *);
extern s32 g_2dfb80;

void Chaser_AdjustNewXp(SOHIT *chaser, XP *pxp, s32 iside) {
    s32 other;

    func_0017F1A0(chaser);
    if (chaser->dhp != 0) {
        other = pxp->side[1 - iside].field_0x8;
        if (other == g_2dfb80) {
            func_0017F5B0(chaser, (void *)other);
        }
    }
}
}

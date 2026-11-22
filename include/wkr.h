/* SPDX-License-Identifier: GPL-3.0-or-later */
/* WKR, a weapon record: what a weapon hit hands to a target's FAbsorb slot (SO slot 75: FAbsorbSoWkr, FAbsorbHbskWkr; STEPGUARD's
   FIsGuardWkrLethal). func_001F7950 (so_sm_1f77c0) fills one, so the offsets agree. FAbsorbHbskWkr hands its words at 0x0 and 0xC on.
   C and C++. */
#ifndef SLY2_WKR_H
#define SLY2_WKR_H
#include "types.h"

struct WKR {
    u8 unknown_0x0[0xC];
    /* 0xC */ s32 grftak;   /* FIsGuardWkrLethal switches on it (0, 1, 0x80000, 0x100000 are not lethal); func_001F7950 sets 0x20000 or 0x40000;
                               FAbsorbHbskWkr passes its address on */
    /* 0x10 */ s32 damage;  /* FIsGuardWkrLethal tests -damage against the guard's field_0x338; func_001F7950 sets it */
    u8 unknown_0x14[0x30];
    /* 0x44 */ u32 flags;   /* FAbsorbSoWkr: nonzero absorbs; FAbsorbHbskWkr tests bit 8 */
};

#if defined(__mips__)
typedef char check_WKR_flags[((unsigned int)&((struct WKR *)0)->flags == 0x44) ? 1 : -1];
#endif
#endif

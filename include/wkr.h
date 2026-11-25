/* SPDX-License-Identifier: GPL-3.0-or-later */
/* WKR, a weapon record: what a weapon hit hands to a target's FAbsorb slot (SO slot 75: FAbsorbSoWkr, FAbsorbHbskWkr; STEPGUARD's
   FIsGuardWkrLethal). func_001F7950 (so_sm_1f77c0) fills one, so the offsets agree. FAbsorbHbskWkr hands its words at 0x0 and 0xC on.
   C and C++. */
#ifndef SLY2_WKR_H
#define SLY2_WKR_H
#include "types.h"
#include "dl.h"

struct WKR {
    /* 0x0 */ struct SO *psoSource;  /* PaloAbsorbWkr (it skips a record of the same source), func_001F7410, func_001F7950 */
    /* 0x4 */ void *ppartSource;     /* PaloAbsorbWkr compares it like the source; func_001F7410 sets the shape that took the hit */
    /* 0x8 */ struct LO *ploTarget;  /* PaloAbsorbWkr hands it to func_001A5BF0; func_001F7410 (PaloFindWkrAbsorber's result), func_001F7950 set it */
    /* 0xC */ s32 grftak;   /* FIsGuardWkrLethal switches on it (0, 1, 0x80000, 0x100000 are not lethal); func_001F7950 sets 0x20000 or 0x40000;
                               FAbsorbHbskWkr passes its address on */
    /* 0x10 */ s32 damage;  /* FIsGuardWkrLethal tests -damage against the guard's field_0x338; func_001F7950 sets it */
    u8 unknown_0x14[0xC];
    /* 0x20 */ QW pos;      /* func_001F7410 (the other side's position), func_001F7950 (PosLoWorld) */
    /* 0x30 */ QW vel;      /* func_001F7410, func_001F7950 (the velocity vector) */
    u8 unknown_0x40[0x4];
    /* 0x44 */ u32 flags;   /* FAbsorbSoWkr: nonzero absorbs; FAbsorbHbskWkr tests bit 8; PaloAbsorbWkr stores GrficFromAlo's result */
    /* 0x48 */ struct SO *psoAbsorbed; /* PaloAbsorbWkr: the object that absorbed it */
    /* 0x4C */ f32 tAbsorb;   /* PaloAbsorbWkr stamps the clock, ExpireSwWkrs drops the record 0.25 s later */
    /* 0x50 */ DLE dle;     /* PaloAbsorbWkr: the record's link in SW::dlWkr */
    u8 unknown_0x58[0x8];
};

#if defined(__mips__)
typedef char check_WKR_flags[((unsigned int)&((struct WKR *)0)->flags == 0x44) ? 1 : -1];
typedef char check_WKR_size[(sizeof(struct WKR) == 0x60) ? 1 : -1];
#endif
#endif

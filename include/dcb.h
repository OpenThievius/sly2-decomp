/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The world's two small pools of 12-byte records, SW::adcb and SW::aoptset (sw.h; the C view swview.h has them too):
   DCB, an object callback (PdcbAllocSw hands one out; an LO's pdcb is the head of its chain: func_001A5D58 links one in,
   func_001A5D98 runs them), and OPTSET, an entry of the option-set pool (func_00210120 hands one out; func_0013E818 fills the
   first two words, an option id and an offset). C and C++. */
#ifndef SLY2_DCB_H
#define SLY2_DCB_H
#include "types.h"

struct LO;

struct DCB {
    /* 0x0 */ void (*pfn)(struct LO *plo, void *pv);
    /* 0x4 */ void *pv;
    /* 0x8 */ struct DCB *pdcbNext;
};

struct OPTSET {
    /* 0x0 */ s32 oid;
    /* 0x4 */ s32 ib;
    u8 unknown_0x8[0x4];
};
#endif

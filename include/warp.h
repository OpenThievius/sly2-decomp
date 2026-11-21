/* SPDX-License-Identifier: GPL-3.0-or-later */
/* WARP, a warp volume: class 0x1A of retail's class table, derived from LO (include/lo.h). The fields are read by its own
   functions (InitWarp, LoadWarpFromBrx, Warp_SetState, Warp_Start, UpdateWarp, WARP_AddTask: the PloFindSpawn file, 0x227FE8). C++ only. */
#ifndef SLY2_WARP_H
#define SLY2_WARP_H
#include "lo.h"

/* A warp volume: class 0x1A (from LO; its volume is at 0xEC, its flags in the LO's grfSw). */
struct WARP : LO {
    u8 unknown_0x50[0xEC - 0x50];
    /* 0xEC */ void *pcbsp;       /* UpdateWarp: the volume the focus is tested against */
    u8 unknown_0xF0[0x130 - 0xF0];
    /* 0x130 */ int fLinked;      /* func_002280D0 */
    /* 0x134 */ int fChained;     /* Warp_Start: a warp follows this one */
    /* 0x138 */ int field_0x138;  /* UpdateWarp: selects the transition flags (0x20) */
    /* 0x13C */ int state;        /* Warp_SetState, UpdateWarp */
    /* 0x140 */ float tState;     /* Warp_SetState: time of the last change */
    /* 0x144 */ sptr desc;        /* LoadWarpFromBrx, UpdateWarp, func_00228518 */
    /* 0x148 */ int cdesc;        /* LoadWarpFromBrx, UpdateWarp */
    /* 0x14C */ sptr *adesc;      /* LoadWarpFromBrx, UpdateWarp */
    /* 0x150 */ int field_0x150;  /* InitWarp (0x189), UpdateWarp */
    /* 0x154 */ int field_0x154;  /* InitWarp (-1), UpdateWarp */
    /* 0x158 */ float tWarp;      /* Warp_Start, UpdateWarp */
    /* 0x15C */ float dtRetry;    /* UpdateWarp */
    /* 0x160 */ float delay;      /* Warp_Start */
    /* 0x164 */ int ctask;        /* Warp_Start, WARP_AddTask */
    /* 0x168 */ u8 atask[0x20];   /* Warp_Start, WARP_AddTask */
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(WARP, pcbsp, 0xEC);
SLY2_OFFSET_CHECK(WARP, fLinked, 0x130);
SLY2_OFFSET_CHECK(WARP, ctask, 0x164);
#endif
#endif

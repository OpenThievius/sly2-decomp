/* SPDX-License-Identifier: GPL-3.0-or-later */
/* STREAMAMB, the stream emitter (0x3C0 bytes, allocated from SNDSYSTEM::heapStreamAmb by NewStreamAmb): AMB (amb.h) plus a volume
   per kind and the slot sources AddAmbSlotSource fills. Fields are read by InitStreamAmb, AddAmbSlotSource and GetStreamAmbKind
   (readers listed). C++ only. */
#ifndef SLY2_STREAMAMB_H
#define SLY2_STREAMAMB_H
#include "amb.h"

/* one source of a slot: an object, its range and its volume (AddAmbSlotSource) */
struct AMBSLOTSOURCE {
    /* 0x0 */ s32 palo;
    /* 0x4 */ f32 lmMin;
    /* 0x8 */ f32 lmMax;                /* AddAmbSlotSource widens it by 1.0 when it equals lmMin */
    /* 0xC */ f32 vol;
};

struct STREAMAMB : AMB {
    /* 0x70 */ f32 vol[6];              /* InitStreamAmb sets all 1.0 */
    u8 unknown_0x88[0x18];
    /* 0xA0 */ s32 count[6];            /* AddAmbSlotSource: sources in each slot */
    /* 0xB8 */ AMBSLOTSOURCE src[6][8]; /* AddAmbSlotSource */
    /* 0x3B8 */ s32 grfStart;           /* InitStreamAmb stores its third argument; GetStreamAmbKind tests bit 4 */
    u8 unknown_0x3BC[4];
};

#if defined(__mips__)
typedef char check_STREAMAMB_size[(sizeof(STREAMAMB) == 0x3C0) ? 1 : -1];
#endif
#endif

/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SLOTSO: class 96 of retail's class table, 0x250 bytes, derived from SO (include/so.h). Its vtable holds UpdateSlotSo (slot 16),
   AccelSlotSoRotation (70), FAbsorbSlotSoWkr (75) and its init function func_001B0B78 (7); the functions named *SlotSo* take it.
   The name is ours, from those functions. A field here is read by a matched method of this class at that offset, and no matched
   function reads the offset differently; the readers are listed. C++ only. */
#ifndef SLY2_SLOTSO_H
#define SLY2_SLOTSO_H
#include "so.h"

struct CRV;
struct ACT;
struct ASEG;

/* One of the six 0xC-byte entries at 0x17C: func_001B0B78 sets oid to -1 and def from a table of six words. */
struct SLOTDEF {
    /* 0x0 */ s32 oid;
    /* 0x4 */ struct ASEG *paseg; /* ResolveSlotSoAsegs stores the resolved aseg of the handle at 0; func_001B0D08 reads it (GSpeedSlotSoAseg) */
    /* 0x8 */ s32 def;
};

struct SLOTSO : SO {
    /* 0x150 */ f32 field_0x150;       /* func_001B0B78 sets it to 400 */
    /* 0x154 */ f32 field_0x154;       /* func_001B0B78 sets it to 800 */
    /* 0x158 */ f32 field_0x158;       /* func_001B0B78 sets it to 2 */
    /* 0x15C */ f32 field_0x15C;       /* func_001B0B78 sets it to 6 */
    /* 0x160 */ f32 field_0x160;       /* func_001B0B78 sets it to 6 */
    /* 0x164 */ f32 field_0x164;       /* func_001B0B78 sets it to 10 */
    /* 0x168 */ f32 dtFade;            /* UpdateSlotSo; func_001B0B78 sets it to 1 */
    /* 0x16C */ struct CRV *pcrvWander; /* UpdateSlotSo, func_001B0D90 */
    u8 unknown_0x170[0x4];
    /* 0x174 */ f32 uWander;           /* func_001B0D90: the position along pcrvWander */
    /* 0x178 */ f32 duWander;          /* func_001B0D90 */
    /* 0x17C */ SLOTDEF aslot[6];      /* func_001B0B78 fills six entries (oid -1, def from a table); entry 3's second word is the
                                       field_0x1A4 of HandleSlotSoMessage (compared with word 0x14 of the message's ACT) */
    /* 0x1C4 */ struct ACT *pactAnim;  /* UpdateSlotSo */
    /* 0x1C8 */ void *field_0x1C8;    /* FAbsorbSlotSoWkr: an object whose slot-51 entry it calls with an event */
    /* 0x1CC */ f32 field_0x1CC;      /* func_001B0B78 sets it to 300 */
    /* 0x1D0 */ f32 field_0x1D0;      /* func_001B0B78 sets it to 1000 */
    /* 0x1D4 */ s32 kindAngular;       /* func_001B0CA8 stores pxfAngular's kind after loading; func_001B1328 hands it back to SetXfKind */
    /* 0x1D8 */ f32 radHeading;        /* FSlotSoFacingHeading */
    u8 unknown_0x1DC[0x44];
    /* 0x220 */ s32 state;             /* UpdateSlotSo, FAbsorbSlotSoWkr; func_001B0B78 sets it to -1 */
    u8 unknown_0x224[0x4];
    /* 0x228 */ f32 tNext;             /* UpdateSlotSo */
    /* 0x22C */ f32 tFade;             /* UpdateSlotSo */
    /* 0x230 */ s32 field_0x230;      /* func_001B0B78 sets it to -1 */
    u8 unknown_0x234[0x1C];
};

#if defined(__mips__)
SLY2_SIZE_CHECK(SLOTSO, 0x250);
SLY2_OFFSET_CHECK(SLOTSO, dtFade, 0x168);
SLY2_OFFSET_CHECK(SLOTSO, pcrvWander, 0x16C);
SLY2_OFFSET_CHECK(SLOTSO, uWander, 0x174);
SLY2_OFFSET_CHECK(SLOTSO, aslot, 0x17C);
SLY2_OFFSET_CHECK(SLOTSO, field_0x1CC, 0x1CC);
SLY2_OFFSET_CHECK(SLOTSO, field_0x230, 0x230);
SLY2_OFFSET_CHECK(SLOTSO, pactAnim, 0x1C4);
SLY2_OFFSET_CHECK(SLOTSO, field_0x1C8, 0x1C8);
SLY2_OFFSET_CHECK(SLOTSO, kindAngular, 0x1D4);
SLY2_OFFSET_CHECK(SLOTSO, radHeading, 0x1D8);
SLY2_OFFSET_CHECK(SLOTSO, state, 0x220);
SLY2_OFFSET_CHECK(SLOTSO, tNext, 0x228);
SLY2_OFFSET_CHECK(SLOTSO, tFade, 0x22C);
#endif
#endif

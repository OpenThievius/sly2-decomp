/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SLY, the player as Sly: class 53 of retail's class table, 0x2060 bytes, derived from JT (include/jt.h); NewSly is its factory and
   its vtable (0x2D2E98) holds InitSly (7), LoadSlyFromBrx (14), UpdateJtBounds (49), SetSlyHide (87), UseSlyGadget (100) and
   others of its own. The name follows those functions. A field here is read or set by one of those methods (slot given). C++ only. */
#ifndef SLY2_SLY_H
#define SLY2_SLY_H
#include "jt.h"

struct PART;
struct TARGET;
struct ASEG;
struct ASEGBL;
struct ASEGA;
struct ALO;

/* a sweep's blend and its blended segment: ChooseJtSweepTarget sets the blend and reblends the segment */
struct BL {
    f32 aw[6];
};
struct SWEEP {
    BL bl;
    struct ASEGBL *pasegbl;
};

struct SLY : JT {
    u8 unknown_0x1320[0x1B4];
    /* 0x14D4 */ struct ASEG *apasegHide[2]; /* SetJtJtcs (states 10, 11) */
    u8 unknown_0x14DC[0x244];
    /* 0x1720 */ void *apasegJts[0x2C]; /* BindJtStepAseg (slot 90) binds the entry jts indexes, entry 0 when it is empty; the count is the room
                                           left before the carry state InitSly starts at 0x17D0, not a measured one */
    /* 0x17D0 */ u8 carry[0x30]; /* the carry state: Carry_SetState */
    /* 0x1800 */ struct ASEG *pasegCarry; /* SetJtJtcs (state 0) */
    u8 unknown_0x1804[0x7C];
    /* 0x1880 */ s32 cbounds; /* UpdateJtBounds (slot 49) */
    u8 unknown_0x1884[0xC];
    /* 0x1890 */ QW abounds[3]; /* UpdateJtBounds extends the bounds by each of the first cbounds; at most 3, ptarget follows */
    /* 0x18C0 */ struct TARGET *ptarget; /* the cane's target: FFaceSlyAimTarget (slot 92) faces it, ChooseJtSweepTarget sets it */
    /* 0x18C4 */ struct JTCSINFO *pjtcsinfo; /* SetJtJtcs: its 0x130 is the leaving sound */
    /* 0x18C8 */ s32 jts; /* the state: NSlyActionCategory (85), FAllowBinocSly (94), BindJtStepAseg (90), JT_FInvulnerable (76), func_0018A428 (50) */
    u8 unknown_0x18CC[0xC];
    /* 0x18D8 */ s32 jtcs; /* SetJtJtcs */
    /* 0x18DC */ f32 tJtcs; /* SetJtJtcs */
    /* 0x18E0 */ struct ASEGA *pasegaJtcs; /* SetJtJtcs: ApplyAsegToHandle's handle */
    /* 0x18E4 */ s32 field_0x18E4;
    u8 unknown_0x18E8[0x4];
    /* 0x18EC */ s32 field_0x18EC;
    u8 unknown_0x18F0[0xB0];
    /* 0x19A0 */ struct PART *apartHide[3]; /* SetSlyHide (87) */
    /* 0x19AC */ f32 rBounds; /* UpdateJtBounds */
    /* 0x19B0 */ f32 tJtcsNext; /* SetJtJtcs */
    u8 unknown_0x19B4[0xC];
    /* 0x19C0 */ struct ALO *paloCane; /* SetJtJtcs: its position */
    u8 unknown_0x19C4[0x40];
    /* 0x1A04 */ SWEEP asweep[4]; /* SetJtJtcs (states 4 to 7) */
    /* 0x1A74 */ struct ASEG *pasegJtcs8;
    /* 0x1A78 */ struct ASEG *pasegJtcs9;
    u8 unknown_0x1A7C[0xC];
    /* 0x1A88 */ void *field_0x1A88; /* SetJtJtcs: func_001F2AD0 */
    u8 unknown_0x1A8C[0x18];
    /* 0x1AA4 */ f32 field_0x1AA4; /* func_0018A428 (50) */
    u8 unknown_0x1AA8[0x238];
    /* 0x1CE0 */ struct ASEG *apasegJtcs[15]; /* SetJtJtcs (states 12 to 21 from 0, 22 and 23 at 13 and 14) */
    u8 unknown_0x1D1C[0x2C4];
    /* 0x1FE0 */ s32 field_0x1FE0; /* UseSlyGadget (100) */
    /* 0x1FE4 */ s32 field_0x1FE4; /* UseSlyGadget (100) */
    u8 unknown_0x1FE8[0x64];
    /* 0x204C */ s32 field_0x204C; /* UseSlyGadget (100) */
    u8 unknown_0x2050[0x10];
};

#if defined(__mips__)
SLY2_SIZE_CHECK(SLY, 0x2060);
SLY2_OFFSET_CHECK(SLY, cbounds, 0x1880);
SLY2_OFFSET_CHECK(SLY, abounds, 0x1890);
SLY2_OFFSET_CHECK(SLY, apasegJts, 0x1720);
SLY2_OFFSET_CHECK(SLY, ptarget, 0x18C0);
SLY2_OFFSET_CHECK(SLY, jts, 0x18C8);
SLY2_OFFSET_CHECK(SLY, apartHide, 0x19A0);
SLY2_OFFSET_CHECK(SLY, rBounds, 0x19AC);
SLY2_OFFSET_CHECK(SLY, field_0x1AA4, 0x1AA4);
SLY2_OFFSET_CHECK(SLY, field_0x1FE0, 0x1FE0);
SLY2_OFFSET_CHECK(SLY, field_0x1FE4, 0x1FE4);
SLY2_OFFSET_CHECK(SLY, field_0x204C, 0x204C);
#endif
#endif

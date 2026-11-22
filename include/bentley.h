/* SPDX-License-Identifier: GPL-3.0-or-later */
/* BENTLEY, the player as Bentley: class 55 of retail's class table, 0x1880 bytes, derived from JT (include/jt.h). Its vtable
   (0x2CB230) holds InitBentley (7), PostBentleyLoad (15), HandleBentleyMessage (5), AdjustBentleyNewXp (55),
   FInvulnerableBentley (76), NBentleyActionCategory (85), SetBentleyMode (88), UseBentleyGadget (100) and others of its own.
   The name follows those functions. A field here is read or set by one of those methods (slot given) or by two other readers
   that agree. C++ only. */
#ifndef SLY2_BENTLEY_H
#define SLY2_BENTLEY_H
#include "jt.h"

struct ASEG;
struct LO;

/* One of Bentley's six gadget entries: InitBentley sets each gadget, UseBentleyGadget leases a clone from the pool. */
struct BENTLEYSLOT {
    /* 0x0 */ s32 gadget;
    /* 0x4 */ void *ppool;
    /* 0x8 */ struct LO *plo;
};

struct BENTLEY : JT {
    void *PvBlendState1() { return (char *)this + 0x1320; } /* the run blend InitBentley starts for state 1 (func_0020B840, 0x73): SetBentleyState resets its footsteps (ResetRunBlendFootsteps) */
    void *PvBlendState7() { return (char *)this + 0x1600; } /* the same for state 7 */
    void *PvLookRig() { return (char *)this + 0x1710; } /* the look rig InitBentley starts at 0x1710: UpdateBentleyAim, HandleBentleyMessage and SetBentleyAimState pass its address */
    u8 unknown_0x1320[0xB0];
    /* 0x13D0 */ s32 state; /* the state: InitBentley (7) sets -1; AdjustBentleyNewXp (55), FInvulnerableBentley (76), NBentleyActionCategory (85), func_00135D80 (90), func_00135FF0 (94), func_00135E40 (98) */
    /* 0x13D4 */ f32 tState; /* when the state was set: UpdateBentleyActive (from UpdateBentley, slot 16) */
    u8 unknown_0x13D8[0x2D8];
    /* 0x16B0 */ s32 field_0x16B0; /* InitBentley sets -1 */
    /* 0x16B4 */ BENTLEYSLOT *pslotActive; /* UseBentleyGadget (100) sets it; HandleBentleyMessage (5) */
    u8 unknown_0x16B8[0x4];
    /* 0x16BC */ s32 aimState; /* the aim state: InitBentley (7) sets -1; UpdateBentleyAim, SetBentleyAimState (bentleyview.h) */
    u8 unknown_0x16C0[0xC];
    /* 0x16CC */ s32 field_0x16CC; /* HandleBentleyMessage (5) compares the sender of message 9 with it before ThrowBentleyBomb (a method of the class: one reader) */
    u8 unknown_0x16D0[0x8];
    /* 0x16D8 */ s32 field_0x16D8; /* ThrowBentleyBomb: the pool selector, 0 or 1 (Bentley's own function: one reader) */
    /* 0x16DC */ s32 field_0x16DC; /* ThrowBentleyBomb: pool for selector 0 (Bentley's own function: one reader) */
    /* 0x16E0 */ s32 field_0x16E0; /* ThrowBentleyBomb: pool for selector 1 (Bentley's own function: one reader) */
    /* 0x16E4 */ struct LAUNCH *field_0x16E4; /* ThrowBentleyBomb: the launcher whose target it sets (Bentley's own function: one reader) */
    u8 unknown_0x16E8[0x8];
    /* 0x16F0 */ QW posTarget; /* the bomb target: CalcBentleyBombTarget and ThrowBentleyBomb (two readers) */
    /* 0x1700 */ f32 field_0x1700; /* ThrowBentleyBomb sets it from a constant (Bentley's own function: one reader) */
    u8 unknown_0x1704[0x10];
    /* 0x1714 */ s32 stateLookRig; /* the state of the look rig at 0x1710 (LOOKRIG::state, set -1 by InitLookRig): UpdateBentleyAim reads it, the rig's own functions use it at +4 */
    u8 unknown_0x1718[0xE8];
    /* 0x1800 */ s32 field_0x1800; /* InitBentley sets -1 */
    u8 unknown_0x1804[0x18];
    /* 0x181C */ s32 field_0x181C; /* SetBentleyState (state 0 picks its animation by it), UpdateBentleyAim (two readers agree) */
    u8 unknown_0x1820[0x4];
    /* 0x1824 */ BENTLEYSLOT aslot[6]; /* InitBentley sets each gadget; HandleBentleyMessage (5) walks them */
    /* 0x186C */ struct LO *ploGadget; /* HandleBentleyMessage (5) leases it */
    /* 0x1870 */ s32 field_0x1870; /* InitBentley sets 5 */
    /* 0x1874 */ s32 field_0x1874; /* UseBentleyGadget (100) */
    u8 unknown_0x1878[0x8];
};

#if defined(__mips__)
SLY2_SIZE_CHECK(BENTLEYSLOT, 0xC);
SLY2_SIZE_CHECK(BENTLEY, 0x1880);
SLY2_OFFSET_CHECK(BENTLEY, state, 0x13D0);
SLY2_OFFSET_CHECK(BENTLEY, tState, 0x13D4);
SLY2_OFFSET_CHECK(BENTLEY, field_0x16B0, 0x16B0);
SLY2_OFFSET_CHECK(BENTLEY, pslotActive, 0x16B4);
SLY2_OFFSET_CHECK(BENTLEY, aimState, 0x16BC);
SLY2_OFFSET_CHECK(BENTLEY, field_0x16CC, 0x16CC);
SLY2_OFFSET_CHECK(BENTLEY, posTarget, 0x16F0);
SLY2_OFFSET_CHECK(BENTLEY, stateLookRig, 0x1714);
SLY2_OFFSET_CHECK(BENTLEY, field_0x1800, 0x1800);
SLY2_OFFSET_CHECK(BENTLEY, field_0x181C, 0x181C);
SLY2_OFFSET_CHECK(BENTLEY, aslot, 0x1824);
SLY2_OFFSET_CHECK(BENTLEY, ploGadget, 0x186C);
SLY2_OFFSET_CHECK(BENTLEY, field_0x1870, 0x1870);
SLY2_OFFSET_CHECK(BENTLEY, field_0x1874, 0x1874);
#endif
#endif

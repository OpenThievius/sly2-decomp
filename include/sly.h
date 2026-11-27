/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SLY, the player as Sly: class 53 of retail's class table, 0x2060 bytes, derived from JT (include/jt.h); NewSly is its factory and
   its vtable (0x2D2E98) holds InitSly (7), LoadSlyFromBrx (14), UpdateJtBounds (49), SetSlyHide (87), UseSlyGadget (100) and
   others of its own. The name follows those functions. A field here is read or set by one of those methods (slot given). C++ only. */
#ifndef SLY2_SLY_H
#define SLY2_SLY_H
#include "jt.h"

struct PART;
/* the object AddJtHangBodyReaction pushes its reaction into: +4 is the body it passes to AddSoAcceleration */
struct HANGBODY {
    u8 unknown_0x0[0x4];
    /* 0x4 */ struct SO *pso;
};
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
    /* The parts InitSly starts in place (their layouts are local to the part's own functions): InitSly passes each its own address,
       AdjustSlyNewXp passes the one at 0x1FF0 on (func_001374E0) */
    void *PvPart1320() { return (char *)this + 0x1320; }
    void *PvPart1C30() { return (char *)this + 0x1C30; }
    void *PvPart1FF0() { return (char *)this + 0x1FF0; }
    u8 unknown_0x1320[0x1B0];
    /* 0x14D0 */ void *field_0x14D0; /* bevy_player_input_from_pad_cm */
    /* 0x14D4 */ struct ASEG *apasegHide[2]; /* SetJtJtcs (states 10, 11) */
    u8 unknown_0x14DC[0x244];
    /* 0x1720 */ void *apasegJts[0x2C]; /* BindJtStepAseg (slot 90) binds the entry jts indexes, entry 0 when it is empty; the count is the room
                                           left before the carry state InitSly starts at 0x17D0, not a measured one */
    /* 0x17D0 */ u8 carry[0x30]; /* the carry state: Carry_SetState */
    /* 0x1800 */ struct ASEG *pasegCarry; /* SetJtJtcs (state 0) */
    u8 unknown_0x1804[0x50];
    /* 0x1854 */ s32 field_0x1854; /* StartAttach (case 6 stores its target); guess, one reader */
    u8 unknown_0x1858[0x28];
    /* 0x1880 */ s32 cbounds; /* UpdateJtBounds (slot 49) */
    u8 unknown_0x1884[0xC];
    /* 0x1890 */ QW abounds[3]; /* UpdateJtBounds extends the bounds by each of the first cbounds; at most 3, ptarget follows */
    /* 0x18C0 */ struct TARGET *ptarget; /* the cane's target: FFaceSlyAimTarget (slot 92) faces it, ChooseJtSweepTarget sets it */
    /* 0x18C4 */ struct LO *ploJtcs; /* the object of the jtcs state (was pjtcsinfo; c8 settled it from its readers): an LO, GetJtHangHeading
                                       calls its PmatWorld (LO slot 31), func_0018A350 its PosLoWorld, HandleSlyMessage compares it with a
                                       message's sender, AddSafePointOnMember reads its member at 0x100, UpdateJmpBodyState stores the jump's
                                       JMPASEGA (jmp.h: an LO) here; SetJtJtcs (not landed) reads a word at its 0x130 */
    /* 0x18C8 */ s32 jts; /* the state: NSlyActionCategory (85), FAllowBinocSly (94), BindJtStepAseg (90), JT_FInvulnerable (76), func_0018A428 (50) */
    u8 unknown_0x18CC[0x4];
    /* 0x18D0 */ s32 field_0x18D0; /* bevy_player_input_from_pad_cm */
    /* 0x18D4 */ f32 field_0x18D4; /* AdjustSlyNewXp (slot 55) compares the clock with it in state 5 */
    /* 0x18D8 */ s32 jtcs; /* SetJtJtcs */
    /* 0x18DC */ f32 tJtcs; /* SetJtJtcs */
    /* 0x18E0 */ struct ASEGA *pasegaJtcs; /* SetJtJtcs: ApplyAsegToHandle's handle */
    /* 0x18E4 */ s32 field_0x18E4;
    /* 0x18E8 */ s32 field_0x18E8; /* reader: UpdateJtCaneInput (a Sly method) tests it in the cane's charge state */
    /* 0x18EC */ s32 field_0x18EC;
    /* 0x18F0 */ s32 field_0x18F0; /* UpdateJmpBodyState (state 21, after testing class 0x35) saves it around SetJmpState and restores it;
                                      StartNextSeqnodeRecord (AddJsgContext_file) sets it from a record argument after the class 0x35 test (two readers) */
    u8 unknown_0x18F4[0xC];
    /* 0x1900 */ struct HANGBODY *phangbody; /* AddJtHangBodyReaction (slot 105) */
    u8 unknown_0x1904[0x2C];
    /* 0x1930 */ QW accelHang;               /* AddJtHangBodyReaction: AddSoAcceleration's vector */
    /* 0x1940 */ QW accelAngularHang;        /* AddJtHangBodyReaction: AddSoAngularAcceleration's vector */
    u8 unknown_0x1950[0x50];
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
    u8 unknown_0x1AA8[0x118];
    /* 0x1BC0 */ void *field_0x1BC0; /* bevy_player_input_from_pad_cm */
    u8 unknown_0x1BC4[0x8];
    /* 0x1BCC */ sptr field_0x1BCC; /* HandleSlyMessage (Sly slot 5): the object func_001F1E20 found, stored before func_001424E0 starts the attachment */
    u8 unknown_0x1BD0[0x4];
    /* 0x1BD4 */ s32 field_0x1BD4; /* HandleSlyMessage: tested with field_0x10DC before the search */
    u8 unknown_0x1BD8[0x108];
    /* 0x1CE0 */ struct ASEG *apasegJtcs[15]; /* SetJtJtcs (states 12 to 21 from 0, 22 and 23 at 13 and 14) */
    /* 0x1D1C */ void *field_0x1D1C; /* bevy_player_input_from_pad_cm */
    u8 unknown_0x1D20[0xC];
    /* 0x1D2C */ s32 field_0x1D2C; /* bevy_player_input_from_pad_cm */
    u8 unknown_0x1D30[0x280];
    union {
        /* 0x1FB0 */ GADGETSLOT aslotSly[4]; /* the four gadget slots (0xC bytes each, JT::aslot's layout): func_0018D6F8 maps gadgets 0x1A, 0x25, 0x26 and 0x29 to them; HandleSlyMessage (Sly slot 5) reads each slot's plo and passes the slot to func_0018D698 */
        struct {
            /* 0x1FB0 */ s32 field_0x1FB0; /* InitSly (slot 7) sets 0x1A; four records of 0xC bytes follow, their first word set by it */
            u8 unknown_0x1FB4[0x8];
            /* 0x1FBC */ s32 field_0x1FBC; /* InitSly sets 0x25 */
            u8 unknown_0x1FC0[0x8];
            /* 0x1FC8 */ s32 field_0x1FC8; /* InitSly sets 0x26 */
            u8 unknown_0x1FCC[0x8];
            /* 0x1FD4 */ s32 field_0x1FD4; /* InitSly sets 0x29 */
            u8 unknown_0x1FD8[0x8];
        };
    };
    /* 0x1FE0 */ s32 field_0x1FE0; /* UseSlyGadget (100) */
    /* 0x1FE4 */ s32 field_0x1FE4; /* UseSlyGadget (100) */
    u8 unknown_0x1FE8[0x2C];
    /* 0x2014 */ f32 field_0x2014; /* bevy_player_input_from_pad_cm */
    u8 unknown_0x2018[0x8];
    /* 0x2020 */ f32 field_0x2020; /* bevy_player_input_from_pad_cm */
    u8 unknown_0x2024[0x8];
    /* 0x202C */ f32 field_0x202C; /* bevy_player_input_from_pad_cm */
    u8 unknown_0x2030[0x8];
    /* 0x2038 */ void *field_0x2038; /* bevy_player_input_from_pad_cm */
    u8 unknown_0x203C[0x8];
    /* 0x2044 */ void *pemitter; /* UseSlyGadget (100): VirtualRefPtr_Assign takes its address, with the emitter of a time gadget */
    u8 unknown_0x2048[0x4];
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
SLY2_OFFSET_CHECK(SLY, phangbody, 0x1900);
SLY2_OFFSET_CHECK(SLY, accelHang, 0x1930);
SLY2_OFFSET_CHECK(SLY, accelAngularHang, 0x1940);
SLY2_OFFSET_CHECK(SLY, field_0x1AA4, 0x1AA4);
SLY2_OFFSET_CHECK(SLY, field_0x1FE0, 0x1FE0);
SLY2_OFFSET_CHECK(SLY, field_0x1FE4, 0x1FE4);
SLY2_OFFSET_CHECK(SLY, field_0x204C, 0x204C);
SLY2_OFFSET_CHECK(SLY, pemitter, 0x2044);
SLY2_OFFSET_CHECK(SLY, field_0x14D0, 0x14D0);
SLY2_OFFSET_CHECK(SLY, field_0x18D0, 0x18D0);
SLY2_OFFSET_CHECK(SLY, field_0x1BC0, 0x1BC0);
SLY2_OFFSET_CHECK(SLY, field_0x1D1C, 0x1D1C);
SLY2_OFFSET_CHECK(SLY, field_0x1D2C, 0x1D2C);
SLY2_OFFSET_CHECK(SLY, field_0x2014, 0x2014);
SLY2_OFFSET_CHECK(SLY, field_0x2020, 0x2020);
SLY2_OFFSET_CHECK(SLY, field_0x202C, 0x202C);
SLY2_OFFSET_CHECK(SLY, field_0x2038, 0x2038);
SLY2_OFFSET_CHECK(SLY, field_0x18F0, 0x18F0);
#endif
#endif

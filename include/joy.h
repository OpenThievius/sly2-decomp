/* SPDX-License-Identifier: GPL-3.0-or-later */
/* JOY, a controller: what PO::pjoy points at (include/po.h only forward-declares it), and the global one at 0x2DFC00 (B_002DFC00).
   Goal_FillVjoy writes the stick of the one a goal fills (GOAL::FillVjoy). A field is read by two functions that agree, or by a
   method of the player (the object is then PO::pjoy). C and C++. */
#ifndef SLY2_JOY_H
#define SLY2_JOY_H
#include "types.h"

struct JOY {
    u8 unknown_0x0[0x18];
    /* 0x18 */ f32 radStick;  /* the stick's angle: UpdateMurrayActive, UpdateMurrayCarry; Goal_FillVjoy sets the actor's heading */
    /* 0x1C */ f32 uStick;    /* the stick's magnitude: UpdateMurrayActive, UpdateMurrayCarry; Goal_FillVjoy clears it */
    u8 unknown_0x20[0x10];
    /* 0x30 */ u32 grfbtn;    /* the buttons held: UpdateMurrayActive, UpdateMurrayCarry */
    u8 unknown_0x34[0x4C];
    /* 0x80 */ s32 field_0x80; /* UpdateJt (JT slot 16) tests 1 on the player's pjoy before GrfbtnVjoyPressedWithin */
    u8 unknown_0x84[0x1030];
    /* 0x10B4 */ u32 grfbtnLatest; /* of B_002DFC00: UpdateJt tests 0x108 before ConsumeJoyButton; _MatchCodes reads it */
};
#endif

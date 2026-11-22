/* SPDX-License-Identifier: GPL-3.0-or-later */
/* JOY, a controller: what PO::pjoy points at (include/po.h only forward-declares it), and the global one at 0x2DFC00 (B_002DFC00).
   Goal_FillVjoy writes the stick of the one a goal fills (GOAL::FillVjoy). A field is read by two functions that agree, or by a
   method of the player (the object is then PO::pjoy). C and C++.
   PRIVATE COPY of include/joy.h (worker W_new_1c3df8): adds the fields VJOY_constructor and SetVjoyMode write (they are the
   class's own constructor and mode setter, so one function each is enough) and names the mode at 0x80 (GetPoVjoyMode, a PO
   method, reads it as -1 without a joy). */
#ifndef SLY2_JOY_H
#define SLY2_JOY_H
#include "types.h"

struct JOY {
    /* 0x0 */ s32 field_0x0;  /* VJOY_constructor clears it */
    /* 0x4 */ s32 field_0x4;  /* VJOY_constructor clears it */
    u8 unknown_0x8[0x4];
    /* 0xC */ const void *pvtbl; /* VJOY_constructor stores retail's vtable (D_002CA240) here */
    u8 unknown_0x10[0x8];
    /* 0x18 */ f32 radStick;  /* the stick's angle: UpdateMurrayActive, UpdateMurrayCarry; Goal_FillVjoy sets the actor's heading */
    /* 0x1C */ f32 uStick;    /* the stick's magnitude: UpdateMurrayActive, UpdateMurrayCarry; Goal_FillVjoy clears it */
    u8 unknown_0x20[0x10];
    /* 0x30 */ u32 grfbtn;    /* the buttons held: UpdateMurrayActive, UpdateMurrayCarry, FVjoyButtonHeld */
    u8 unknown_0x34[0x44];
    /* 0x78 */ s32 field_0x78; /* SetVjoyMode sets 0xFFFF when the mode becomes 1 */
    /* 0x7C */ s32 field_0x7C; /* VJOY_constructor stores its second argument */
    /* 0x80 */ s32 vjoym;      /* the mode: SetVjoyMode (sets), VJOY_constructor (-1), GetPoVjoyMode; UpdateJt tests 1 on the player's */
    u8 unknown_0x84[0x1030];
    /* 0x10B4 */ u32 grfbtnLatest; /* of B_002DFC00: UpdateJt tests 0x108 before ConsumeJoyButton; _MatchCodes reads it */
};
#endif

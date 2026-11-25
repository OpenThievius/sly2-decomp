/* SPDX-License-Identifier: GPL-3.0-or-later */
/* JOY, a controller: what PO::pjoy points at (include/po.h only forward-declares it), and the global one at 0x2DFC00 (B_002DFC00).
   Goal_FillVjoy writes the stick of the one a goal fills (GOAL::FillVjoy). A field is read by two functions that agree, or by a
   method of the player (the object is then PO::pjoy). C and C++.
   VJOY_constructor and SetVjoyMode are the class's own constructor and mode setter, so one function each is enough for the fields
   they write; GetPoVjoyMode (a PO method) reads the mode at 0x80 as -1 without a joy. The controller fields from 0x1000 are read and
   written by the controller's own methods (src/joy/InitJoy_file.cpp: UpdateJoy, SetJoyJoys, FReadJoy, FJoyButtonPressed,
   UpdateJoyNavX/Y): their offsets are certain, their names are guesses from use. */
#ifndef SLY2_JOY_H
#define SLY2_JOY_H
#include "types.h"
#include "clq.h"
#include "rumble.h"

struct JOY {
    /* 0x0 */ s32 field_0x0;  /* VJOY_constructor clears it */
    /* 0x4 */ s32 field_0x4;  /* VJOY_constructor clears it */
    u8 unknown_0x8[0x4];
    /* 0xC */ const void *pvtbl; /* VJOY_constructor stores retail's vtable (D_002CA240) here */
    /* 0x10 */ f32 xLeft;     /* the stick's x: UpdateVjoy passes its address to UpdateVjoyStick (px); UpdateSeqnodeVjoy sets it; ResetVjoy clears it */
    /* 0x14 */ f32 yLeft;     /* the stick's y: UpdateVjoy (py), UpdateSeqnodeVjoy; ResetVjoy clears it */
    /* 0x18 */ f32 radStick;  /* the stick's angle: UpdateMurrayActive, UpdateMurrayCarry; Goal_FillVjoy sets the actor's heading */
    /* 0x1C */ f32 uStick;    /* the stick's magnitude: UpdateMurrayActive, UpdateMurrayCarry; Goal_FillVjoy clears it */
    /* 0x20 */ f32 field_0x20;  /* ResetVjoy clears it */
    /* 0x24 */ f32 field_0x24;  /* ResetVjoy clears it */
    /* 0x28 */ f32 field_0x28;  /* ResetVjoy clears it */
    /* 0x2C */ f32 field_0x2C;  /* ResetVjoy clears it; UpdateVjoyPressTimes (VJOY's own) tests it above 0 to pick tStickRight's slot */
    /* 0x30 */ u32 grfbtn;    /* the buttons held: UpdateMurrayActive, UpdateMurrayCarry, FVjoyButtonHeld */
    u8 unknown_0x34[0x44];
    /* 0x78 */ s32 field_0x78; /* SetVjoyMode sets 0xFFFF when the mode becomes 1 */
    /* 0x7C */ s32 field_0x7C; /* VJOY_constructor stores its second argument */
    /* 0x80 */ s32 vjoym;      /* the mode: SetVjoyMode (sets), VJOY_constructor (-1), GetPoVjoyMode; UpdateJt tests 1 on the player's */
    /* 0x84 */ struct JOY *pjoyNext; /* the link of the world's list of virtual joysticks (SW::pvjoyFirst): UpdateSw walks it, Sw_Construct's
                                       InitSl gives its offset */
    /* 0x88 */ f32 tButton[16];  /* UpdateVjoyPressTimes (VJOY's own): the clock when each button last went down */
    /* 0xC8 */ f32 tStickLeft[2]; /* the same: the clock of the left stick's last frame with it below or above 0 (index 0 or 1) */
    /* 0xD0 */ f32 tStickRight[2];
    u8 unknown_0xD8[0xF28];
    /* The controller from 0x1000: its own methods (UpdateJoy, SetJoyJoys, FReadJoy, FJoyButtonPressed, UpdateJoyNavX/Y) read and write it. */
    /* 0x1000 */ s32 port;      /* InitJoy stores it; every libpad call passes it */
    /* 0x1004 */ s32 slot;      /* InitJoy stores it */
    /* 0x1008 */ s32 idPad;     /* FReadJoy: the id byte of the last read (buf[1]); a change fails the read; SetJoyJoys clears it with joyk 0 */
    /* 0x100C */ s32 joys;      /* the controller's connection state (SetJoyJoys sets, UpdateJoy switches on it, 3 = reading) */
    /* 0x1010 */ s32 joyk;      /* its kind (SetJoyJoys sets, UpdateJoy switches on it; 4 = pressure-sensitive, 3 and up = rumble) */
    /* 0x1014 */ f32 tJoys;     /* the time of the last SetJoyJoys change: UpdateJoy times out on it */
    /* 0x1018 */ f32 tRead;     /* FReadJoy: the time of the last read; SetJoyJoys clears it */
    /* 0x101C */ f32 tInput;    /* FReadJoy: the time of the last input */
    /* 0x1020 */ s32 dtIdle;    /* FReadJoy: whole seconds since the last input */
    /* 0x1024 */ s32 dirNavX;   /* UpdateJoyNavX: -1 or 1 while the stick or pad repeats along x; SetJoyJoys and ResetJoyNav clear it */
    /* 0x1028 */ s32 dirNavY;   /* UpdateJoyNavY, the same along y */
    /* 0x102C */ f32 tNavX;     /* UpdateJoyNavX: when the next repeat fires */
    /* 0x1030 */ f32 dtNavX;    /* UpdateJoyNavX: the repeat delay */
    /* 0x1034 */ f32 tNavY;     /* UpdateJoyNavY */
    /* 0x1038 */ f32 dtNavY;    /* UpdateJoyNavY */
    /* 0x103C */ f32 xStick;    /* FReadJoy: the left stick (or the pad), x */
    /* 0x1040 */ f32 yStick;    /* y */
    /* 0x1044 */ f32 uStickLeft; /* its magnitude: UpdateJoyNavX/Y compare it with 0.8 and 0.25 */
    /* 0x1048 */ u8 field_0x1048; /* GetJoyXYDeflection's two byte outputs for the left stick (FReadJoy passes their addresses) */
    /* 0x1049 */ u8 field_0x1049;
    u8 unknown_0x104A[0x2];
    /* 0x104C */ s32 field_0x104C; /* GetJoyXYDeflection's int output for the left stick; SetJoyJoys clears it */
    /* 0x1050 */ struct LM lmLeft[4]; /* the left stick's limits: SetJoyJoys resets them, FReadJoy passes them on */
    /* 0x1070 */ f32 xStickRight; /* FReadJoy: the right stick, x */
    /* 0x1074 */ f32 yStickRight;
    /* 0x1078 */ f32 uStickRight;
    /* 0x107C */ u8 field_0x107C; /* the right stick's byte outputs */
    /* 0x107D */ u8 field_0x107D;
    u8 unknown_0x107E[0x2];
    /* 0x1080 */ s32 field_0x1080; /* the right stick's int output; SetJoyJoys clears it */
    /* 0x1084 */ struct LM lmRight[4]; /* the right stick's limits */
    /* 0x10A4 */ f32 dxStickLeft;  /* FReadJoy: the left stick's change per second */
    /* 0x10A8 */ f32 dyStickLeft;
    /* 0x10AC */ f32 dxStickRight;
    /* 0x10B0 */ f32 dyStickRight;
    /* 0x10B4 */ u32 grfbtnLatest; /* of B_002DFC00: UpdateJt tests 0x108 before ConsumeJoyButton; _MatchCodes reads it; FReadJoy sets it */
    /* 0x10B8 */ s32 grfbtnPressed; /* the buttons that went down since they were consumed: FReadJoy sets, FJoyButtonPeek reads, ConsumeJoyButton clears */
    /* 0x10BC */ s32 grfbtnHeld;    /* the buttons held since the last read: FReadJoy, ConsumeJoyButton (0xFFFF when SetJoyJoys resets it) */
    /* 0x10C0 */ u8 pressure[0xC];  /* the pressure bytes of a kind-4 pad: FReadJoy copies them, SetJoyJoys clears them */
    /* 0x10CC */ struct RUMBLE rumble; /* InitRumble, UpdateRumble, TriggerRumbleRumk take its address */
    /* 0x10E8 */ s32 fRumble;       /* rumble enabled: InitJoy sets 1; UpdateJoy and TriggerJoyRumbleRumk test it */
    /* 0x10EC */ f32 uDpad;         /* the deflection FReadJoy gives the pad as a stick: InitJoy sets 1.0 */
};
#endif

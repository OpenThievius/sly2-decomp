/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CLOCK, the game clock: one static global at 0x2DDED0 (g_2dded0). Read as a struct, not a float: Warp_SetState scores 5 when
   the time is declared as a plain float (the load schedules differently). t is the time (Warp_SetState stores it as the time of a
   state change), dt the last frame's length (UpdateWarp). C and C++. A source reads the real time at 0x2DDF0C as g_2dded0.tReal:
   as a member it keeps retail's load and store order where a scalar global does not (FReadJoy, func_001ACC38). */
#ifndef SLY2_CLOCK_H
#define SLY2_CLOCK_H
#include "types.h"

struct CLOCK {
    /* 0x0 */ f32 t;  /* the time: Warp_SetState */
    /* 0x4 */ f32 dt; /* the last frame's length: UpdateWarp */
    /* 0x8 */ f32 rate;     /* the product of arate: RecalcClockRate sets it; MarkClockTick scales the game frame by it */
    /* 0xC */ f32 rateCopy; /* RecalcClockRate copies arate[8] here; MarkClockTick scales the real frame by it */
    /* 0x10 */ f32 field_0x10; /* UpdateSw runs UpdateCmLast only while it is positive */
    u8 unknown_0x14[0x4];
    /* 0x18 */ f32 arate[9]; /* the rate factors: InitClock sets eight to 1.0, SetClockRate sets one by index, RecalcClockRate multiplies them; MarkClockTick scales the scaled frame by arate[3] */
    /* 0x3C */ f32 tReal;  /* the real time (the global g_2ddf0c is this field: 0x2DDED0 + 0x3C): SetJoyJoys, FReadJoy, UpdateJoyNavX/Y,
                              _MatchCodes */
    /* 0x40 */ f32 dtReal; /* the real frame length: FReadJoy divides the stick's change by it */
};

#ifdef __cplusplus
extern "C" CLOCK g_2dded0;
#else
extern struct CLOCK g_2dded0;
#endif
#endif

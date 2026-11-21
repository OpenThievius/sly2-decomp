/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CLOCK, the game clock: one static global at 0x2DDED0 (g_2dded0). Read as a struct, not a float: Warp_SetState scores 5 when
   the time is declared as a plain float (the load schedules differently). t is the time (Warp_SetState stores it as the time of a
   state change), dt the last frame's length (UpdateWarp). C and C++. */
#ifndef SLY2_CLOCK_H
#define SLY2_CLOCK_H
#include "types.h"

struct CLOCK {
    /* 0x0 */ f32 t;  /* the time: Warp_SetState */
    /* 0x4 */ f32 dt; /* the last frame's length: UpdateWarp */
};

#ifdef __cplusplus
extern "C" CLOCK g_2dded0;
#else
extern struct CLOCK g_2dded0;
#endif
#endif

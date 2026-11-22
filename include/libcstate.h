/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The C library's per-program state that the pointer at 0x2C49D4 points to: the error number first (func_00234580 passes its
   address to the number parser as the error slot), the random seed at 0x58 (rand reads and updates it; func_002401C8 returns
   the pointer). Names are ours. C and C++. */
#ifndef SLY2_LIBCSTATE_H
#define SLY2_LIBCSTATE_H
#include "types.h"
typedef struct LIBCSTATE {
    s32 errorNumber;  /* 0x00, func_00234580 */
    u8 unknown_0x4[0x54];
    s32 randomSeed;   /* 0x58, rand */
} LIBCSTATE;
#endif

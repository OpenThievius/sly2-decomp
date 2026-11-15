/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

typedef struct GsDrawEnvHalf {
    char unknown_0x0[0x20];
    u64 xyoffset;
    char unknown_0x28[0x8];
    u64 scissor;
} GsDrawEnvHalf;

void sceGsSetHalfOffset(GsDrawEnvHalf *draw, s16 centerx, s16 centery, s16 halfoff)
{
    s64 ofx;
    s64 ofy;
    u64 y;
    u64 scissor = draw->scissor;
    ofy = (centery - ((u64)((s32)((scissor >> 48) & 0x7FF) + 1) >> 1)) << 4;
    ofx = (centerx - ((u64)((s32)((scissor >> 16) & 0x7FF) + 1) >> 1)) << 4;
    if (halfoff) {
        y = (u64)(ofy + 8) << 32;
    } else {
        y = (u64)ofy << 32;
    }
    draw->xyoffset = (u64)ofx | y;
}

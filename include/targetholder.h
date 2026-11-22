/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The object func_002562B8 and func_002562F0 take: an owner at 0x20 (the object func_001F4BF8 re-queues) and a block of target
   values at 0x24 (a float at 0x8, a halfword at 0x14). Layout from those two; what the object is stays open. C and C++. */
#ifndef SLY2_TARGETHOLDER_H
#define SLY2_TARGETHOLDER_H
#include "types.h"
typedef struct TARGETVALUES {
    u8 unknown_0x0[0x8];
    f32 field_0x8;
    u8 unknown_0xC[0x8];
    s16 field_0x14;
} TARGETVALUES;
typedef struct TARGETHOLDER {
    u8 unknown_0x0[0x20];
    void *owner;           /* 0x20 */
    TARGETVALUES *values;  /* 0x24 */
} TARGETHOLDER;
#endif

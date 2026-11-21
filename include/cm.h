/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CM, the camera manager: one static global at 0x2DDF40 (B_002DDF40). Only what matched code reads is known: two camera
   policies (CPLCY, 0xD0 bytes each) at 0x450, which Warp_Start revokes. C++ only. */
#ifndef SLY2_CM_H
#define SLY2_CM_H
#include "types.h"

struct CPLCY {
    u8 unknown_0x0[0xD0];
};

struct CM {
    u8 unknown_0x0[0x450];
    /* 0x450 */ CPLCY acplcy[2]; /* Warp_Start revokes both */
};

extern "C" CM B_002DDF40; /* the camera manager */

#if defined(__mips__)
typedef char check_CM_acplcy[((unsigned int)&((CM *)0)->acplcy == 0x450) ? 1 : -1];
#endif
#endif

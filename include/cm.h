/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CM, the camera manager: one static global at 0x2DDF40 (B_002DDF40). Only what matched code reads is known: a float at 0x24 the
   attach policy sets, two camera policies (CPLCY, 0xD0 bytes each) at 0x450, which Warp_Start revokes. C++ only. */
#ifndef SLY2_CM_H
#define SLY2_CM_H
#include "types.h"

struct CPLCY {
    u8 unknown_0x0[0xD0];
};

struct CM {
    u8 unknown_0x0[0x24];
    /* 0x24 */ f32 field_0x24; /* ActivateCpattach and DeactivateCplcy store a policy's float here (two readers) */
    u8 unknown_0x28[0x428];
    /* 0x450 */ CPLCY acplcy[2]; /* Warp_Start revokes both */
};

extern "C" CM B_002DDF40; /* the camera manager */

#if defined(__mips__)
typedef char check_CM_field_0x24[((unsigned int)&((CM *)0)->field_0x24 == 0x24) ? 1 : -1];
typedef char check_CM_acplcy[((unsigned int)&((CM *)0)->acplcy == 0x450) ? 1 : -1];
#endif
#endif

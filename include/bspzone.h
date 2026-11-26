/* SPDX-License-Identifier: GPL-3.0-or-later */
/* BSPZONE, a convex-volume zone: class 0x105 of CploFindSwObjectsByClass, an XFM (xfm.h, 0xE0 bytes) with a point-in-BSP test and an
   inside state. func_00227350 starts it, func_00227380 loads it, func_002273F0 tests a point against it and func_00227440 changes its
   state; the camera manager ranks the zones the camera may be in (func_0014E078, func_0014E000) and follows the first one
   (bevy_camera_cm_14e148). Two files read it: the two agree on 0xE0, 0x110 and 0x114. C++ only. */
#ifndef SLY2_BSPZONE_H
#define SLY2_BSPZONE_H
#include "types.h"
#include "xfm.h"

struct CBSP;

struct BSPC {
    u8 unknown_0x0[0xC];
    /* 0xC */ struct CBSP *pcbsp;  /* func_002273F0 asks it whether a point is inside */
};

struct BSPZONE : XFM {
    /* 0xE0 */ u32 grf;            /* func_00227380 reads it from the file (U32Read); bevy_camera_cm_14e148 copies it into CM::field_0x14 */
    /* 0xE4 */ s32 field_0xE4;     /* func_0014E000: the second key, larger first (func_00227380 skips it: a gap there) */
    /* 0xE8 */ struct BSPC bspc;   /* func_00227380 reads it (ReadBspc against geom) */
    /* 0xF8 */ u8 geom[0x18];      /* func_00227380 reads it (ReadGeom); the size is the gap up to state */
    /* 0x110 */ s32 state;         /* func_00227350 sets -1; func_00227440 sets 0 or 1 (inside); func_0014E000's first key (larger first),
                                      func_0014E078 takes the first zone only when it is 1 */
    /* 0x114 */ f32 tState;        /* the clock time of the last change of state; func_0014E000's third key (smaller first) */
    u8 unknown_0x118[0x8];         /* 0x120 bytes: func_0014E000's last key is the pointers' difference, divided by 0x120 */
};

#if defined(__mips__)
SLY2_SIZE_CHECK(BSPZONE, 0x120);
SLY2_OFFSET_CHECK(BSPZONE, state, 0x110);
#endif
#endif

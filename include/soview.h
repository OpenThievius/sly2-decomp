/* SPDX-License-Identifier: GPL-3.0-or-later */
/* C view of SO (so.h), which is C++ only: the part the sources of src/sm-so and src/so written in C read, with so.h's names and
   offsets; a C++ source uses SO itself. Same idea as guardview.h and jtview.h. C only. */
#ifndef SLY2_SOVIEW_H
#define SLY2_SOVIEW_H
#ifdef __cplusplus
#error "soview.h is the C view of so.h: include so.h in C++"
#endif
#include "types.h"

struct OXA;
struct XF;

/* SO's vtable up to slot 53 (a slot is 8 bytes: delta, index, function; slot n at 8 * n) */
struct SOVT {
    u8 unknown_0x0[0x1A8];
    /* 0x1A8 */ s16 deltaPoxaAlloc;                  /* slot 53: SO::PoxaAlloc */
    /* 0x1AA */ s16 indexPoxaAlloc;
    /* 0x1AC */ struct OXA *(*pfnPoxaAlloc)(void *);
};

/* PHYS (phys.h): SO::pphys's block, up to its field 0xD0 */
struct PHYSVIEW {
    u8 unknown_0x0[0xD0];
    /* 0xD0 */ f32 field_0xD0;                       /* PHYS::field_0xD0: SetSoMass rescales it */
};

struct SOVIEW {
    u8 unknown_0x0[0xC];
    /* 0xC */ const struct SOVT *vt;                 /* the vtable pointer */
    u8 unknown_0x10[0x38];
    /* 0x48 */ s32 field_0x48;                      /* func_00204C60 compares it with the object a STEP discards xps for */
    u8 unknown_0x4C[0xC];
    /* 0x58 */ struct XF *pxfLinear;                 /* SO::pxfLinear */
    /* 0x5C */ struct XF *pxfAngular;                /* SO::pxfAngular */
    /* 0x60 */ struct XF *pxfRoot;                   /* SO::pxfRoot: RadYawSo reads its world matrix */
    u8 unknown_0x64[0x84];
    /* 0xE8 */ struct PHYSVIEW *pphys;               /* SO::pphys */
    /* 0xEC */ struct OXA *poxa;                     /* SO::poxa */
};
#endif

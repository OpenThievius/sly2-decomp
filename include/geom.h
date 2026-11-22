/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GEOM, one 0xB0-byte element of SO::ageom (include/so.h, which only forward-declares it): a collision shape bound to the XF it
   follows. Other sources still declare their own views of the same elements (ProjectSoTransform, FFilterOxa, GetBombVictims). C and C++. */
#ifndef SLY2_GEOM_H
#define SLY2_GEOM_H
#include "xf.h"

struct GEOM {
    /* 0x00 */ struct XF *pxf;          /* the transform the shape follows: func_001F3900, func_001F38A8 */
    /* 0x04 */ struct SO *pso;          /* its owner: func_001F38A8 passes it to func_001F4BF8; GetBombVictims reads it too */
    u8 unknown_0x8[0x8];
    /* 0x10 */ u64 grf;                 /* func_001F3900 tests bit 50; FFilterOxa and ProjectSoTransform read the same word */
    u8 unknown_0x18[0x8];
    /* 0x20 */ struct MATRIX4 matWorld; /* func_001F3900 copies the XF's world matrix here */
    u8 unknown_0x60[0x18];
    /* 0x78 */ u8 field_0x78[0x18];     /* func_001F38A8 passes both blocks to TransformGeom with the XF's world matrix */
    /* 0x90 */ u8 field_0x90[0x18];
    /* 0xA8 */ s32 generationBound;     /* func_001F38A8: the XF generation the two blocks were computed for */
    /* 0xAC */ s32 generationMat;       /* func_001F3900: the XF generation matWorld was copied at */
};

#if defined(__mips__)
typedef char check_GEOM_size[(sizeof(struct GEOM) == 0xB0) ? 1 : -1];
typedef char check_GEOM_matWorld[((unsigned int)&((struct GEOM *)0)->matWorld == 0x20) ? 1 : -1];
#endif
#endif

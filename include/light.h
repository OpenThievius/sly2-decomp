/* SPDX-License-Identifier: GPL-3.0-or-later */
/* LIGHT, a light object (RebuildLight's argument, ub-light module). Private copy for the typed pass: C++ derives it from LO
   (lo.h); the C sources get the same fields over an opaque 0x50-byte LO prefix. */
#ifndef SLY2_LIGHT_H
#define SLY2_LIGHT_H
#include "sly2.h"
#ifdef __cplusplus
#include "lo.h"
#include "xf.h"

struct LIGHT : LO {
    /* 0x50 */ XF *pxf;                  /* func_001A3460 (LIGHT's slot 17, after LO's): reads its generation (XF 0xA4) */
    u8 unknown_0x54[0x8C];
    /* 0xE0 */ s32 mode;                 /* RebuildLight (switch), SetLightKind, func_001A3B38 */
    /* 0xE4 */ s32 generation;           /* func_001A3460 raises it to the XF's generation and rebuilds */
    u8 unknown_0xE8[0x8];
    /* 0xF0 */ VECTOR hsv;               /* RebuildLight, SetLightHighlightColor */
    u8 unknown_0x100[0x18];
    /* 0x118 */ s32 index;               /* the light's slot in SW::aplight: RemoveLightFromSw clears it and stores -1 */
    u8 unknown_0x11C[0x4];
    /* 0x120 */ s32 block[12];           /* the 0x30-byte block RebuildLight fills (its first word is the mode) and func_001A4AD8 copies to the packet */
    /* 0x150 */ float strength;          /* RebuildLight, func_001A3610 */
    /* 0x154 */ float cone;              /* RebuildLight, func_001A3630 */
    /* 0x158 */ s32 field_0x158;         /* InitLight (the constructor, slot 7) sets 1 */
    /* 0x15C */ s32 fExcludeDynamicObjects; /* SetLightFExcludeDynamicObjects; func_001A3B38 */
    /* 0x160 */ s32 fDynamic;            /* SetLightDynamic; func_001A3B38, func_001A3260 (finds a light that is not dynamic) */
    /* 0x164 */ float rangeA;            /* RebuildLight; SetLightFallOff copies the pair (rangeA, rangeB) */
    /* 0x168 */ float rangeB;
};
#else
#include "xf.h"
struct LIGHT {
    u8 unknown_0x0[0x50];
    /* 0x50 */ struct XF *pxf;
    u8 unknown_0x54[0x8C];
    /* 0xE0 */ s32 mode;
    /* 0xE4 */ s32 generation;
    u8 unknown_0xE8[0x8];
    /* 0xF0 */ struct VECTOR hsv;
    u8 unknown_0x100[0x50];
    /* 0x150 */ float strength;
    /* 0x154 */ float cone;
};
#endif
#endif

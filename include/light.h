/* SPDX-License-Identifier: GPL-3.0-or-later */
/* LIGHT, a light object (RebuildLight's argument, ub-light module). Private copy for the typed pass: C++ derives it from LO
   (lo.h); the C sources get the same fields over an opaque 0x50-byte LO prefix. */
#ifndef SLY2_LIGHT_H
#define SLY2_LIGHT_H
#include "sly2.h"
#ifdef __cplusplus
#include "lo.h"
#include "xf.h"
#include "bytes8.h"

/* twelve bytes copied as one block (the xyz of a position): RebuildLight */
struct BYTES12 {
    BYTES8 first;
    s32 second;
};

struct LIGHT : LO {
    /* 0x50 */ XF *pxf;                  /* func_001A3460 (LIGHT's slot 17, after LO's): reads its generation (XF 0xA4) */
    u8 unknown_0x54[0x8C];
    /* 0xE0 */ s32 mode;                 /* RebuildLight (switch), SetLightKind, func_001A3B38 */
    /* 0xE4 */ s32 generation;           /* func_001A3460 raises it to the XF's generation and rebuilds */
    u8 unknown_0xE8[0x8];
    /* 0xF0 */ VECTOR hsv;               /* RebuildLight, SetLightHighlightColor */
    /* 0x100 */ VECTOR pos;              /* RebuildLight (fills it: the light's world position, or zero for a directional one; the one reader) */
    /* 0x110 */ float scaleA;            /* RebuildLight: 1 for a directional light, else the linear fit of rangeA/rangeB, times the larger of strength and hsv.z */
    /* 0x114 */ float scaleB;            /* the same */
    /* 0x118 */ s32 index;               /* the light's slot in SW::aplight: RemoveLightFromSw clears it and stores -1 */
    u8 unknown_0x11C[0x4];
    union {
        /* 0x120 */ s32 block[12];       /* the 0x30-byte block RebuildLight fills (its first word is the mode) and func_001A4AD8 copies to the packet */
        struct {                         /* the words of the block RebuildLight names (it fills them: certain) */
            /* 0x120 */ s32 modeCopy;
            /* 0x124 */ float angleA;    /* ConvertAngleStrength's outputs */
            /* 0x128 */ float angleB;    /* stored negated */
            /* 0x12C */ float fitA;      /* FitLinearFunction's outputs (kind 1) */
            /* 0x130 */ float color[3];  /* the light's rgb, divided by the larger of strength and hsv.z */
            /* 0x13C */ float alpha;     /* strength, divided the same way */
            /* 0x140 */ BYTES12 posCopy;  /* the light's position, or the first row of its world matrix (kind 0) */
            /* 0x14C */ float fitB;
        };
    };
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

/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GEOM, one 0xB0-byte element of SO::ageom (include/so.h, which only forward-declares it): a collision shape bound to the XF it
   follows. Other sources still declare their own views of the same elements (ProjectSoTransform, FFilterOxa, GetBombVictims). C and C++. */
#ifndef SLY2_GEOM_H
#define SLY2_GEOM_H
#include "xf.h"

struct GEOM {
    /* 0x00 */ struct XF *pxf;          /* the transform the shape follows: func_001F3900, func_001F38A8 */
    /* 0x04 */ struct SO *pso;          /* its owner: func_001F38A8 passes it to func_001F4BF8; GetBombVictims reads it too */
    /* 0x8 */ f32 radius;              /* CloneCloth sets it to the largest vertex length; CSo_LoadFromBrx reads a float into it */
    /* 0xC */ s32 alo;                  /* PpartFindAlo compares it with the id it is given; func_001F6AC8, func_001F6B48 match it with their argument */
#ifdef __cplusplus
    union {
        /* 0x10 */ u64 grf;             /* func_001F3900 tests bit 50; FFilterOxa and ProjectSoTransform read the same word */
        /* 0x10 */ s16 ashGrf[4];       /* the same word in halves: func_001F7A68 and func_001F7410 read the damage dealt at 0x14 (ashGrf[2], a short) */
    };
#else
    /* 0x10 */ u64 grf;
#endif
    /* 0x18 */ s32 grftak;              /* the take flags the shape answers to: func_001F7410 passes them to PaloFindWkrAbsorber, func_001F7A68 swaps them
                                           between two values, func_001F6BC8 sets them on the shapes whose alo it is given */
    /* 0x1C */ s32 cfixed;             /* CloneCloth copies it and splits the vertex block at it; CSo_LoadFromBrx reads a short into it */
    /* 0x20 */ struct MATRIX4 matWorld; /* func_001F3900 copies the XF's world matrix here */
    /* 0x60 */ struct GEOM *pgeomNext; /* the link of its object's OXA::dlGeom (PoxaAllocSw: InitDl ibDle 0x60; AddSoGeomToOxa appends): IntersectSwBoundingSphere
                                          and bevy_camera_follow_push_out walk it */
    u8 unknown_0x64[0x4];
    /* 0x68 */ u8 field_0x68[0x10];     /* CloneCloth hands both blocks to CloneBspc as the tree (0x68) and its planes (0x90); CSo_LoadFromBrx passes 0x68 to ReadBspc */
    /* 0x78 */ u8 field_0x78[0x18];     /* func_001F38A8 passes both blocks to TransformGeom with the XF's world matrix */
    /* 0x90 */ u8 field_0x90[0x18];
    /* 0xA8 */ s32 generationBound;     /* func_001F38A8: the XF generation the two blocks were computed for */
    /* 0xAC */ s32 generationMat;       /* func_001F3900: the XF generation matWorld was copied at */
};

#if defined(__mips__)
typedef char check_GEOM_size[(sizeof(struct GEOM) == 0xB0) ? 1 : -1];
typedef char check_GEOM_pgeomNext[((unsigned int)&((struct GEOM *)0)->pgeomNext == 0x60) ? 1 : -1];
typedef char check_GEOM_matWorld[((unsigned int)&((struct GEOM *)0)->matWorld == 0x20) ? 1 : -1];
#endif
#endif

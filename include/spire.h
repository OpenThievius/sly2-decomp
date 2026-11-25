/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SPIRE: a spire object (retail's mangled InitSpire__FP5SPIRE; list at B_003E142C). Our name for the layout: the link is the DLE at
   0x100 that Spire_AddLoHierarchy's list (ibDle) threads, dzMax is read by the 0x19B110 module and set by InitSpire, ptn is read by PostSpireLoad. C and C++. */
#ifndef SLY2_SPIRE_H
#define SLY2_SPIRE_H
#include "types.h"
#include "dl.h"

struct TN;

struct SPIRE {
    u8 unknown_0x0[0xE0];
    /* 0xE0 */ s32 cvert;       /* LoadSpireFromBrx (the class's own loader): the vertex count */
    /* 0xE4 */ QW *avert;       /* LoadSpireFromBrx: the vertices, read as vectors of 16 bytes */
    /* 0xE8 */ s32 ctri;        /* LoadSpireFromBrx: the triangle count */
    /* 0xEC */ s32 *atri;       /* LoadSpireFromBrx: three vertex indices a triangle */
    /* 0xF0 */ s32 *aneighbor;  /* LoadSpireFromBrx: three neighbour triangles a triangle */
    u8 unknown_0xF4[0xC];
    /* 0x100 */ struct DLE dle; /* the link of the world's spire list (B_003E142C) */
    /* 0x108 */ f32 dzMax;      /* InitSpire sets FLT_MAX; the 0x19B110 module's closest-point search reads it */
    u8 unknown_0x10C[0x4];
    /* 0x110 */ struct TN *ptn; /* PostSpireLoad (the class's PostLoad) hands it to SetTnTns when it is set */
};
#endif

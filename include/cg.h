/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CG, the path graph of a pathzone (its vertices, faces and edges, built by SetupDefaultPathzone and CPathZone_LoadFromBrx, hooked up
   by HookupCg, searched by PcgtPointInCgSafe and FindPathAStar): six words, a count and an array each. The pathzone holds one at
   0xE0. CGV is the vertex (0x20 bytes: IcgvFromPcgv shifts the pointer difference by 5), CGE the edge (0x10 bytes: PcgtPointInCgSafe
   steps through the array as its nodes). C and C++. */
#ifndef SLY2_CG_H
#define SLY2_CG_H
#include "types.h"

struct CGV {
    u8 unknown_0x0[0x20];
};

struct CGF;

struct CGE {
    u8 unknown_0x0[0x10];
};

struct CG {
    /* 0x00 */ s32 ccgv;       /* SetupDefaultPathzone, CPathZone_LoadFromBrx: the vertex count */
    /* 0x04 */ struct CGV *acgv; /* the vertices: IcgvFromPcgv subtracts it from a vertex pointer */
    /* 0x08 */ s32 ccgf;       /* the face count */
    /* 0x0C */ struct CGF *acgf; /* the faces */
    /* 0x10 */ s32 ccge;       /* the edge count: PcgtPointInCgSafe */
    /* 0x14 */ struct CGE *acge; /* the edges: FFindClosestPointInCg passes it as the first node to PcgtPointInCgSafe */
};
#endif

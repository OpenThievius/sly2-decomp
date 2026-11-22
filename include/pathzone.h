/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The pathzone system of src/new_1c0920 (0x1BF900 to 0x1C2900): PATHZONE (an LO holding a convex-graph record, a sweep-and-prune
   index of the obstacles in it), OBSTACLE (a curve with a box), PZLINK (a link between two pathzones with up to six targets),
   TARGETSLOT, PZEP and the world's PZGRAPH (SW::ppzgraph) that ties them together. The C view has only the PATHZONE words the
   C thunks use. Names are ours, from what those functions do (HookupPzgraph, BuildPzgraphAdjacency, AddPathzoneObstacle,
   GrowPathzoneSlots, CobstacleFindPathzoneBox, PostPzlinkLoad, ...). Readers are named per field; every class is the one whose
   own methods read it. */
#ifndef SLY2_PATHZONE_H
#define SLY2_PATHZONE_H
#include "types.h"
#include "cg.h"
#include "dl.h"
#ifdef __cplusplus
#include "lo.h"
#include "crv.h"

/* a sweep endpoint of the sweep-and-prune index: the coordinate on one axis, whether it opens a slot's interval, and the slot */
struct PZEP {
    /* 0x0 */ f32 g;
    /* 0x4 */ u16 fMin; /* 1 for the lower end of the interval, 0 for the upper */
    /* 0x6 */ u16 islot; /* the obstacle slot (0xFF for the two sentinels) */
};

struct PATHZONE;

/* an obstacle in a pathzone: a curve (CRV: its points are apos) with a world box */
struct OBSTACLE : CRV {
    u8 unknown_0x180[0x20];
    /* 0x1A0 */ QW posMin;          /* AddPathzoneObstacle: the box the sweep index is searched with, and inserted by x and y */
    /* 0x1B0 */ QW posMax;
    u8 unknown_0x1C0[0x1C];
    /* 0x1DC */ PATHZONE *ppathzone; /* AddPathzoneObstacle sets it */
};

/* a sweep query's state, 0x40 bytes (CobstacleFindPathzoneBox, ResetPathzoneQuery): the slots inside each axis's interval as bit sets
   and the cursors into each axis's endpoints; stamp ties it to the PATHZONE::stamp it was made against */
struct PATHQUERY {
    /* 0x00 */ u32 agrfX[4];
    /* 0x10 */ u32 agrfY[4];
    /* 0x20 */ s32 stamp;
    /* 0x24 */ s32 iepMinX;
    /* 0x28 */ s32 iepMaxX;
    /* 0x2C */ s32 iepMinY;
    /* 0x30 */ s32 iepMaxY;
    u8 unknown_0x34[0xC];
};

/* a pathzone: an LO with a convex-graph record at 0xE0 (the CG that ClsgClipEdgeToCg, FClipEdgeToCg and FFindClosestPointInCg take
   by address) and, from 0xF8, the sweep-and-prune index of its obstacles */
struct PATHZONE : LO {
    u8 unknown_0x50[0x90];
    /* 0xE0 */ struct CG cg;      /* the path graph (cg.h): ClsgClipEdgeToCg, FClipEdgeToCg, FFindClosestPointInCg take its address;
                                     SetupDefaultPathzone and CPathZone_LoadFromBrx fill it */
    /* 0xF8 */ s32 cobstacle;     /* AddPathzoneObstacle, RemovePathzoneObstacle: obstacles held */
    /* 0xFC */ s32 cslot;         /* GrowPathzoneSlots: slots allocated (0, 0x10, 0x80) */
    /* 0x100 */ s32 cep;          /* endpoints in aepX and aepY (two per obstacle plus two sentinels) */
    /* 0x104 */ PZEP *aepX;
    /* 0x108 */ PZEP *aepY;
    /* 0x10C */ OBSTACLE **aslot;  /* the obstacle in each slot, 0 when free */
    /* 0x110 */ s32 field_0x110;  /* InitPathzone (slot 7) sets -1 */
    /* 0x114 */ s32 stamp;        /* the world's stamp when the index last changed: CobstacleFindPathzoneBox resets a query whose stamp differs */
    /* 0x118 */ DL dlItem;        /* InitPathzone: InitDl with the link at 0x60 of each element */
    /* 0x124 */ s32 ipathzone;    /* HookupPzgraph: its index in the graph; InitPathzone sets -1 */
};

/* one target of a PZLINK, 0x20 bytes: a curve (func_001C1F28 reads its middle), an object (its world position) or a fixed position */
struct TARGETSLOT {
    /* 0x00 */ void *crv;
    /* 0x04 */ void *plo;
    u8 unknown_0x8[0x8];
    /* 0x10 */ QW vec;
};

/* a link between two pathzones (class of InitPzlink at slot 7, PostPzlinkLoad 15, AddPzlinkHierarchy 11, RemovePzlinkHierarchy 12) */
struct PZLINK : LO {
    /* 0x50 */ u32 ctarget;        /* func_001C20E8, func_001C2148 append while below 6; PostPzlinkLoad reads the last */
    u8 unknown_0x54[0xC];
    /* 0x60 */ TARGETSLOT atarget[6];
    /* 0x120 */ s32 field_0x120;   /* InitPzlink sets -1 */
    /* 0x124 */ PATHZONE *ppathzoneA; /* PostPzlinkLoad: PpathzoneFindPos at the first target */
    /* 0x128 */ PATHZONE *ppathzoneB; /* at the last */
    u8 unknown_0x12C[0x4];
    /* 0x130 */ QW posA;
    /* 0x140 */ QW posB;
    /* 0x150 */ s32 ipzlink;       /* InitPzlink sets -1; HookupPzgraph sets its index in the graph */
};

/* one pathzone's links in the graph's adjacency (BuildPzgraphAdjacency) */
struct PZADJ {
    /* 0x0 */ s32 count;
    /* 0x4 */ s32 *aitem;
};

/* one edge of the graph, as LoadPzgraphFromBrx reads it */
struct PZENTRY {
    /* 0x0 */ QW *ppos;
    /* 0x4 */ s16 iA;
    /* 0x6 */ s16 iB;
};

/* the world's pathzone graph (0x30 bytes, SW::ppzgraph): LoadPzgraphFromBrx reads the first six words (cint ints are the oids of
   the pathzones), HookupPzgraph fills the pointers, BuildPzgraphAdjacency the adjacency, Add/RemovePzlinkHierarchy the stamp */
struct PZGRAPH {
    /* 0x00 */ s32 cent;
    /* 0x04 */ PZENTRY *aent;
    /* 0x08 */ s32 cvec;
    /* 0x0C */ QW *avec;
    /* 0x10 */ s32 cpathzone;       /* LoadPzgraphFromBrx's cint */
    /* 0x14 */ s32 *aoidPathzone;   /* its aint */
    /* 0x18 */ PATHZONE **appathzone; /* its aintClear (allocated cleared): HookupPzgraph fills it */
    /* 0x1C */ PZADJ *aadj;         /* BuildPzgraphAdjacency */
    /* 0x20 */ s32 cplink;          /* HookupPzgraph */
    /* 0x24 */ PZLINK **applink;
    /* 0x28 */ s32 stamp;           /* AddPzlinkHierarchy, RemovePzlinkHierarchy: the world's pzlinkChange */
    /* 0x2C */ s32 fHookedUp;       /* HookupPzgraph sets 1 */
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(PATHZONE, cobstacle, 0xF8);
SLY2_OFFSET_CHECK(PATHZONE, cg, 0xE0);
SLY2_OFFSET_CHECK(PATHZONE, stamp, 0x114);
SLY2_OFFSET_CHECK(PATHZONE, dlItem, 0x118);
SLY2_OFFSET_CHECK(PATHZONE, ipathzone, 0x124);
SLY2_OFFSET_CHECK(OBSTACLE, posMin, 0x1A0);
SLY2_OFFSET_CHECK(OBSTACLE, ppathzone, 0x1DC);
SLY2_OFFSET_CHECK(PZLINK, atarget, 0x60);
SLY2_OFFSET_CHECK(PZLINK, ppathzoneA, 0x124);
SLY2_OFFSET_CHECK(PZLINK, posA, 0x130);
SLY2_OFFSET_CHECK(PZLINK, ipzlink, 0x150);
SLY2_SIZE_CHECK(PZGRAPH, 0x30);
#endif
#else
struct PATHZONE {
    u8 unknown_0x0[0xE0];
    /* 0xE0 */ struct CG cg;      /* PATHZONE::cg */
};
#endif
#endif

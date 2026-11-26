/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The laser object and its beams (retail 0x1DEDB0 to 0x1DFAD8: LASER, BEAM, SEG, KEY, MQ). Names and meanings are ours, from what
   func_001DEDB0, NotifyLaserXpEnded, ClipLaserBeams and AdvanceLaserBeams do with them: each of those sources used to declare its own
   view of the object, and two of them declared GetLaserBeamPoints with different types. Offsets are the ones all four agree on.
   A LASER is an SO (0x150 bytes, UpdateSo and CSo_LoadFromBrx take it); its own fields start at 0x150. C++. */
#ifndef SLY2_LASER_H
#define SLY2_LASER_H
#include "types.h"
#include "so.h"
#include "oxa.h"

struct KEY { float a, b, c, sDuration, t; };

/* One animated segment of a beam (0xA0 bytes). */
struct SEG {
    u8 unknown_0x0[4];
    /* 0x04 */ int nState;   /* AdvanceLaserBeams: 1 while it plays */
    u8 unknown_0x8[0xC];
    /* 0x14 */ float s;
    /* 0x18 */ int ckey;
    /* 0x1C */ KEY akey[6];
    /* 0x94 */ int ikey;
    u8 unknown_0x98[8];
};

/* One side of a queued contact (0x40 bytes): the contact holds two. The names follow the readers that agree on them: the shape at 0,
   the object at 8 and its root at 0xC (MarkSoCustomContacts and RecalcSwXpMovement in FreeSwMqList_file.cpp, func_001F7410,
   AdjustMurrayNewXp, AdjustVehicleNewXp, AdjustStepXps). ClipLaserBeams hands the first side's pgeom and pos and the second side's pso
   to the weapon record (WKR::ppartSource, pos, ploTarget); NotifyLaserXpEnded compares plo with the laser and with the other object.
   The types are the first readers' (int for the shape and the root). */
struct SIDE {
    /* 0x00 */ int pgeom;
    u8 unknown_0x4[4];
    /* 0x08 */ void *plo;
    /* 0x0C */ int pso;
    /* 0x10 */ QW pos;
    u8 unknown_0x20[0x20];
};

/* A queued contact of a beam (0xB0 bytes): ClipLaserBeams reads the nearest hit (pgeom, pos, pso, s), NotifyLaserXpEnded walks the chain and
   compares plo with the contact's two sides (SIDE, 0x40 bytes each, the first one starts here). */
struct MQ {
    /* 0x00 */ SIDE aside[2];
    /* 0x80 */ QW normal;          /* AdjustVehicleNewXp, AdjustMurrayNewXp: the contact's normal (PxpAdd builds it from the velocities, as velBase) */
    /* 0x90 */ float gScale;       /* PxpAdd stores its gScale argument here; AdjustStepXps picks the kind-0xE contact with the smallest, func_001D2DD0 the largest */
    /* 0x94 */ float friction;     /* AdjustVehicleNewXp sets it (PxpAdd's gB) */
    /* 0x98 */ float bounce;       /* AdjustVehicleNewXp sets it (PxpAdd's gC) */
    /* 0x9C */ int kind;           /* AdjustStepXps (0xE), func_001F90D0 in SolveSw_file.cpp (0xD, 0xE: its XP is this record) */
    /* 0xA0 */ float s;
    u8 unknown_0xA4[8];
    /* 0xAC */ MQ *pmqNext;
};

struct BEAM {
    SEG aseg[2];       /* 0x000 */
    float sFull;       /* 0x140 */
    float sClipped;    /* 0x144 */
    MQ *pmqFirst;      /* 0x148 */
    u8 unknown_0x14C[4];
};

struct LASERFX { void *plo; void *paseg; void *pasega; void *pchn; };

struct LASER : SO {
    u8 unknown_0x150[0x48];         /* func_001DE2D8 reads an oid and a class filter here (one reader, not a method: its own view) */
    /* 0x198 */ int cbeam;
    /* 0x19C */ BEAM *abeam;
    /* 0x1A0 */ LASERFX afx[2];
    /* 0x1C0 */ float dt;
};

#endif

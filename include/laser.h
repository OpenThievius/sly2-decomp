/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The laser object and its beams (retail 0x1DEDB0 to 0x1DFAD8: LASER, BEAM, SEG, KEY, MQ). Names and meanings are ours, from what
   func_001DEDB0, NotifyLaserXpEnded, ClipLaserBeams and AdvanceLaserBeams do with them: each of those sources used to declare its own
   view of the object, and two of them declared GetLaserBeamPoints with different types. Offsets are the ones all four agree on. C++. */
#ifndef SLY2_LASER_H
#define SLY2_LASER_H
#include "types.h"

struct KEY { float a, b, c, sDuration, t; };

/* One animated segment of a beam (0xA0 bytes). */
struct SEG { char pad0[4]; int nState; char pad1[0x14 - 8]; float s; int ckey; KEY akey[6]; int ikey; char pad2[0xA0 - 0x98]; };

/* One side of a queued contact (0x40 bytes). */
struct SIDE { char pad0[8]; void *pso; char pad1[0x34]; };

/* A queued contact of a beam (0xB0 bytes): ClipLaserBeams reads the nearest hit (plo, pos, pgeom, s), NotifyLaserXpEnded walks the chain and
   compares pso with the contact's two sides (SIDE, 0x40 bytes each, the first one starts here). */
struct MQ {
    int plo;               /* 0x00 */
    char pad0[4];
    void *pso;             /* 0x08, the first side's object */
    char pad1[0x10 - 0xC];
    QW pos;                /* 0x10 */
    char pad2[0x4C - 0x20];
    int pgeom;             /* 0x4C */
    char pad3[0xA0 - 0x50];
    float s;               /* 0xA0 */
    char pad4[0xAC - 0xA4];
    MQ *pmqNext;           /* 0xAC */
};

struct BEAM {
    SEG aseg[2];       /* 0x000 */
    float sFull;       /* 0x140 */
    float sClipped;    /* 0x144 */
    MQ *pmqFirst;      /* 0x148 */
    char pad[0x150 - 0x14C];
};

struct DLOWNER { char pad[0x70]; u64 grf; };

struct LASERFX { void *plo; void *paseg; void *pasega; void *pchn; };

struct LASER {
    char pad0[0xEC];
    DLOWNER *powner;   /* 0x0EC */
    char pad1[0x198 - 0xF0];
    int cbeam;         /* 0x198 */
    BEAM *abeam;       /* 0x19C */
    LASERFX afx[2];    /* 0x1A0 */
    float dt;          /* 0x1C0 */
};

#endif

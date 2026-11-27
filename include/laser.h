/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The laser object and its beams (retail 0x1DEDB0 to 0x1DFAD8: LASER, BEAM, SEG, KEY). Names and meanings are ours, from what
   func_001DEDB0, NotifyLaserXpEnded, ClipLaserBeams and AdvanceLaserBeams do with them: each of those sources used to declare its own
   view of the object, and two of them declared GetLaserBeamPoints with different types. Offsets are the ones all four agree on.
   A beam's contacts (MQ and SIDE here before) are the shared XP and XPD of include/xp.h.
   A LASER is an SO (0x150 bytes, UpdateSo and CSo_LoadFromBrx take it); its own fields start at 0x150. C++. */
#ifndef SLY2_LASER_H
#define SLY2_LASER_H
#include "types.h"
#include "so.h"
#include "oxa.h"
#include "xp.h"

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

struct BEAM {
    SEG aseg[2];       /* 0x000 */
    float sFull;       /* 0x140 */
    float sClipped;    /* 0x144 */
    XP *pxpFirst;      /* 0x148: the beam's contacts (XP, include/xp.h), linked through pxpNext */
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

/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The animation curves the XF's goal evaluators read (0x12B520-0x12C800): ACRB (Bezier keys of 0x30 bytes), ACRBL (keys of 0x20 bytes),
   ACRAXIS (one float array per axis). The key finders (IkeyFindAcrb, func_0012BB70, func_0012C708) read the count at 4 and the keys
   at 8; the segment loaders copy a key pair into the XF's goal blocks (posGoal, velGoal, the QW at 0xE0, the QW at 0xF0). C++ only. */
#ifndef SLY2_ACR_H
#define SLY2_ACR_H
#include "xf.h"

struct VECTOR3 { f32 x, y, z; };

/* a Bezier key, 0x30 bytes: the position, its time, the incoming and outgoing tangent */
struct KEYB {
    /* 0x00 */ VECTOR3 pos;
    /* 0x0C */ f32 t;
    /* 0x10 */ QW in;
    /* 0x20 */ QW out;
};

struct ACRB {
    u8 unknown_0x0[4];
    /* 0x04 */ s32 ckey;   /* IkeyFindAcrb */
    /* 0x08 */ KEYB *akey; /* IkeyFindAcrb, EvaluateAcrb, func_0012B738 */
};

/* a key of 0x20 bytes: the position, its time and one tangent */
struct KEYBL {
    /* 0x00 */ VECTOR3 pos;
    /* 0x0C */ f32 t;
    /* 0x10 */ QW tan;
};

struct ACRBL {
    u8 unknown_0x0[4];
    /* 0x04 */ s32 ckey;    /* func_0012BB70 */
    /* 0x08 */ KEYBL *akey; /* func_0012BB70, func_0012BBD0, func_0012BE68 */
};

/* keys given as one array of floats per axis (x, y, z), a shared array of times, and a default value for an axis without keys */
struct ACRAXIS {
    u8 unknown_0x0[4];
    /* 0x04 */ s32 ckey;        /* func_0012C708, func_0012C0E0 */
    /* 0x08 */ f32 *atime;      /* func_0012C708, func_0012C0E0, func_0012C768 */
    /* 0x0C */ f32 *aaxis[3];   /* func_0012C768: two floats (value, tangent) per key, or 0 */
    u8 unknown_0x18[8];
    /* 0x20 */ f32 adefault[3]; /* func_0012C768 */
};
#endif

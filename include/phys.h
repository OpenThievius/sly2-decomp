/* SPDX-License-Identifier: GPL-3.0-or-later */
/* PHYS, the physics block of a solid object (SO::pphys, +0xE8, include/so.h). Only the fields a matched reader needs are named;
   the rest are sized gaps. Sources that still declare their own PHYS (several per-function sources keep one with other fields)
   do not include this header. C++ only. */
#ifndef SLY2_PHYS_H
#define SLY2_PHYS_H
#include "lo.h"

struct LINK; /* each reader defines the part of the link it reads */

struct PHYS {
    u8 unknown_0x00[0x60];
    /* 0x60 */ QW linear;     /* ProjectSoTransform: the linear velocity copied from the SO's linear XF */
    /* 0x70 */ QW angular;    /* the angular velocity copied from its angular XF */
    union {
        /* 0x80 */ QW dvGravity;       /* RefOpVectorBallisticVelocity, SolveSw */
        /* 0x80 */ f32 gravity[4];     /* func_001F3590 sets the three lanes, the jump readers take the third (0x88) */
    };
    u8 unknown_0x90[0x10];
    /* 0xA0 */ s32 ctTorque;  /* 3 when the torque is locked (FIsSoLocked, func_001F3590, SolveSw) */
    u8 unknown_0xA4[0x1C];
    /* 0xC0 */ s32 ctForce;   /* 3 when the force is locked */
    u8 unknown_0xC4[0xC];
    /* 0xD0 */ f32 field_0xD0;  /* reader: CSo_LoadFromBrx (read from the brx stream into the freshly allocated block) */
    u8 unknown_0xD4[0x8];
    /* 0xDC */ struct LINK *plink; /* the region link: UpdateSo, TranslateSoToPos, func_001F37C8, the Add/Remove hierarchy pair */
};

SLY2_OFFSET_CHECK(PHYS, linear, 0x60);
SLY2_OFFSET_CHECK(PHYS, angular, 0x70);
SLY2_OFFSET_CHECK(PHYS, dvGravity, 0x80);
SLY2_OFFSET_CHECK(PHYS, ctTorque, 0xA0);
SLY2_OFFSET_CHECK(PHYS, ctForce, 0xC0);
SLY2_OFFSET_CHECK(PHYS, field_0xD0, 0xD0);
SLY2_OFFSET_CHECK(PHYS, plink, 0xDC);
#endif

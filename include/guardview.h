/* SPDX-License-Identifier: GPL-3.0-or-later */
/* C views of STEP (step.h) and STEPGUARD (stepguard.h), which are C++ only: the part of each that the guard code written in C reads,
   with the same names and offsets. A C++ source uses STEP and STEPGUARD themselves. C only. */
#ifndef SLY2_GUARDVIEW_H
#define SLY2_GUARDVIEW_H
#ifdef __cplusplus
#error "guardview.h is the C view of stepguard.h: include stepguard.h in C++"
#endif
#include "types.h"
#include "guard.h"
#include "goals.h"

struct ASEGA;
struct BASIC;
struct SO;

/* the C slice of STEP */
struct STEPVIEW {
    u8 unknown_0x0[0x1B0];
    /* 0x1B0 */ struct MATRIX3Q matHeading; /* func_00209840 (GUARDHEADING's method) copies a rotation into it; STEP declares these bytes
                                               as unknown */
    u8 unknown_0x1E0[0x24];
    /* 0x204 */ s32 field_0x204;            /* STEP::field_0x204: func_00203FA0 sets it */
    /* 0x208 */ struct SO *psoSurface;      /* STEP::psoSurface: func_00203FA0 clears it when field_0x204 becomes set */
};

/* the C slice of STEPGUARD */
struct STEPGUARDVIEW {
    u8 unknown_0x0[0x26C];
    /* 0x26C */ struct GOALSTACK goalstack; /* STEP::pgoalstack() */
    u8 unknown_0x274[0x2C0 - 0x274];
    /* 0x2C0 */ u64 grfsgs;
    u8 unknown_0x2C8[0x338 - 0x2C8];
    /* 0x338 */ s32 field_0x338;
    /* 0x33C */ s32 field_0x33C;
    u8 unknown_0x340[0x34C - 0x340];
    /* 0x34C */ struct ASEGA *pasega;
    u8 unknown_0x350[0x38C - 0x350];
    /* 0x38C */ struct BASIC *pbasicAlert;
    /* 0x390 */ s32 field_0x390;
    /* 0x394 */ s32 cgroup;
    u8 unknown_0x398[0x3A4 - 0x398];
    /* 0x3A4 */ s32 csensed;
    /* 0x3A8 */ s32 cignoredClass;
    u8 unknown_0x3AC[0x3C0 - 0x3AC];
    /* 0x3C0 */ s32 cclassFilter;
    u8 unknown_0x3C4[0x3CC - 0x3C4];
    /* 0x3CC */ struct ALERT *palert;
    u8 unknown_0x3D0[0x4C0 - 0x3D0];
    /* 0x4C0 */ s32 canim;
    u8 unknown_0x4C4[0xC];
    /* 0x4D0 */ struct GUARDANIM aanim[0x20];
    /* 0x8D0 */ struct ANIMREF aarefA[26];
    /* 0xA70 */ struct ANIMREF aarefB[26];
    /* 0xC10 */ struct ANIMREF aarefC[26];
    u8 unknown_0xDB0[0xF3C - 0xDB0];
    /* 0xF3C */ s32 fFlag;
    u8 unknown_0xF40[0xF64 - 0xF40];
    /* 0xF64 */ struct SENSOR *psensor;
    /* 0xF68 */ struct LO *ptargetGoto;
    u8 unknown_0xF6C[0x4];
    /* 0xF70 */ QW posGoto;
    u8 unknown_0xF80[0xFD0 - 0xF80];
    /* 0xFD0 */ struct GUARDHEADING heading;
};
#endif

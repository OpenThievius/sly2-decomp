/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CARRYTHROW, the carry part a JT starts in place (JT::PvCarry() at 0x11B0; MURRAY::PvCarry() at 0x1910 is the second one): no
   vtable, a part of the player. CarryThrow_Init fills it, CarryThrow_Launch throws what it holds, CarryThrow_EnsureBlends and
   CarryThrow_SetState are its other functions, func_00220498 asks it about a target. Not CARRY (carry.h), the LO Murray holds.
   Fields are certain by their readers being the part's own functions.  */
#ifndef SLY2_CARRYTHROW_H
#define SLY2_CARRYTHROW_H
#include "sly2.h"

struct JT;
struct SO;
struct LO;

union CARRYVECTOR { QW q; f32 f[4]; };

struct CARRYTHROW {
    /* 0x00 */ struct JT *pjtOwner; /* CarryThrow_Init stores it; CarryThrow_Launch passes it to the heading weight, CarryThrow_EnsureBlends to every blend */
    /* 0x04 */ s32 state;           /* CarryThrow_Init sets -1 (CarryThrow_SetState); func_00220498 tests -1 and 3 */
    u8 unknown_0x8[0x8];
    /* 0x10 */ struct SO *pso;      /* the carried object: CarryThrow_Launch lets it go; func_00220498 compares it with its target */
    /* 0x14 */ f32 field_0x14;      /* CarryThrow_Init: 1.0 */
    /* 0x18 */ f32 field_0x18;      /* CarryThrow_Init: 1.0 */
    /* 0x1C */ f32 field_0x1C;      /* CarryThrow_Init: 500 */
    /* 0x20 */ f32 field_0x20;      /* CarryThrow_Init: 1500 */
    /* 0x24 */ f32 field_0x24;      /* CarryThrow_Init: 1.5 */
    /* 0x28 */ f32 field_0x28;      /* CarryThrow_Init: 1000 */
    u8 unknown_0x2C[0x4];
    /* 0x30 */ union CARRYVECTOR omega; /* CarryThrow_Init sets (0, 0, 25); CarryThrow_Launch passes it through the heading weight to slot 36 of the carried object */
    /* 0x40 */ u8 ablHold[0x18];   /* CarryThrow_EnsureBlends: the hold blend (EnsureAsegBlendDynamic fills it) */
    /* 0x58 */ void *pasegblHold;  /* CarryThrow_EnsureBlends */
    u8 unknown_0x5C[0xC];
    /* 0x68 */ u8 ablAim[0x30];    /* CarryThrow_EnsureBlends */
    /* 0x98 */ void *pasegblAim;   /* CarryThrow_EnsureBlends */
    u8 unknown_0x9C[0x8];
    /* 0xA4 */ u8 ablThrow[0x18];  /* CarryThrow_EnsureBlends */
    /* 0xBC */ void *pasegblThrow; /* CarryThrow_EnsureBlends */
    /* 0xC0 */ union CARRYVECTOR vecAim;    /* CarryThrow_Init sets (1000, 0, 0) */
    /* 0xD0 */ union CARRYVECTOR vecLaunch; /* CarryThrow_Init sets (42, -73, -50) */
    u8 unknown_0xE0[0x10];
    /* 0xF0 */ QW velocity;         /* CarryThrow_Launch passes it to slot 35 of the carried object */
    u8 unknown_0x100[0x2C];
    /* 0x12C */ struct LO *ploDisplay; /* CarryThrow_Launch removes it (slot 9) when set */
};

#if defined(__mips__)
typedef char check_CARRYTHROW_pso[((unsigned int)&((struct CARRYTHROW *)0)->pso == 0x10) ? 1 : -1];
typedef char check_CARRYTHROW_omega[((unsigned int)&((struct CARRYTHROW *)0)->omega == 0x30) ? 1 : -1];
typedef char check_CARRYTHROW_vecAim[((unsigned int)&((struct CARRYTHROW *)0)->vecAim == 0xC0) ? 1 : -1];
typedef char check_CARRYTHROW_vecLaunch[((unsigned int)&((struct CARRYTHROW *)0)->vecLaunch == 0xD0) ? 1 : -1];
typedef char check_CARRYTHROW_velocity[((unsigned int)&((struct CARRYTHROW *)0)->velocity == 0xF0) ? 1 : -1];
typedef char check_CARRYTHROW_ploDisplay[((unsigned int)&((struct CARRYTHROW *)0)->ploDisplay == 0x12C) ? 1 : -1];
#endif
#endif

/* SPDX-License-Identifier: GPL-3.0-or-later */
/* TN, the tunnel: an LO subclass whose camera policy (CPTN, cplcy.h) follows a curve or steps through a list of camera steps. The
   fields are the ones the functions of src/tn/ and src/tn-rip/ read; SetTnTns is a method of the class (FP2TN), so one reader is
   enough for its fields. C and C++ (the C view has no vtable, the C++ one derives from LO). */
#ifndef SLY2_TN_H
#define SLY2_TN_H
#include "types.h"

#ifdef __cplusplus
#include "lo.h"
struct TN : LO {
    u8 unknown_0x50[0x90];
#else
struct SO;
struct TN {
    u8 unknown_0x0[0x10];
    /* 0x10 */ struct SO *psoParent; /* LO::psoParent: CloneTn passes it to PloCloneLo */
    u8 unknown_0x14[0xCC];
#endif
    /* 0xE0 */ struct SO *psoFocus; /* the focus object the camera policy follows: SetTnTns passes it to SetCmPolicy; UpdateTnCallback sets it */
    /* 0xE4 */ u8 geom[0x18];       /* the collision geometry LoadTnFromBrx reads (CBinaryInputStream_ReadGeom); LoadTnFromBrx is the class's LoadFromBrx (slot 14) */
    /* 0xFC */ u8 bspc[0xC];        /* the BSP the same function reads next (CBinaryInputStream_ReadBspc, with the geometry) */
    /* 0x108 */ void *pcbsp;        /* the BSP's collision tree: UpdateTnCallback (the callback the tunnel registers) asks it for the polygon around the focus (PcgtPointInCbspQuick) */
    /* 0x10C */ struct CRV *pcrv;   /* the curve: CloneTn clones it, LoadTnFromBrx loads it, UpdateCptnClosestPoint measures on it */
    /* 0x110 */ s32 cstep;         /* the number of camera steps: LoadTnFromBrx sizes the world copy of the steps (0x90 bytes each) with it */
    /* 0x114 */ void *pstep;        /* the camera steps: LoadTnFromBrx reads the stack copy, then keeps the world copy */
    /* 0x118 */ void *pstepCurrent; /* the current camera step: func_00221818 sets it, func_00221940 clears it; LoadTnFromBrx points it at the world copy */
    /* 0x11C */ s32 fStepsFixed;    /* LoadTnFromBrx sets 1 once the steps live in the world heap */
    u8 unknown_0x120[0x4];
    /* 0x124 */ s32 fAir;           /* UpdateTnCallback: when it is set the callback always applies the state */
    /* 0x128 */ s32 pri;            /* SetTnTns: the camera policy priority, 2 added */
    /* 0x12C */ s32 fFakeCylinder;  /* UpdateCptnClosestPoint (CPTN's update, slot 6): without a curve, the tunnel is a cylinder around posFake */
    u8 unknown_0x130[0x4];
    /* 0x134 */ s32 tns;            /* SetTnTns: the state, TNS */
    /* 0x138 */ f32 tTns;           /* SetTnTns: the time of the last state change */
    /* 0x13C */ s32 tnsOverride;    /* UpdateTn tests it; UpdateTnCallback, SetTnTnsOverride, InitTn (-1) */
    /* 0x140 */ f32 sClosest;       /* UpdateCptnClosestPoint: the arc length (or angle times radius) of the point closest to the camera's nose */
    u8 unknown_0x144[0xC];
    /* 0x150 */ QW posFake;         /* UpdateCptnClosestPoint: the axis point of the fake cylinder */
    /* 0x160 */ f32 sRadFake;       /* UpdateCptnClosestPoint: the fake cylinder's radius, scales the angle into sClosest */
    /* 0x164 */ s32 flags;          /* InitTn (the constructor, slot 7) sets 7; LoadTnFromBrx clears bit 1 when there is no curve */
    u8 unknown_0x168[0x8];
    /* 0x170 */ f32 field_0x170;    /* InitTn sets 2.0 */
    /* 0x174 */ f32 field_0x174;    /* InitTn sets 1.0 */
    /* 0x178 */ f32 field_0x178;    /* InitTn sets 2.0 */
    /* 0x17C */ f32 field_0x17C;    /* InitTn sets 1.0 */
    /* 0x180 */ s32 field_0x180;    /* InitTn sets -1 */
    u8 unknown_0x184[0x1C];
    /* 0x1A0 */ QW field_0x1A0;     /* InitTn copies a quadword (D_002C41C0) here */
    /* 0x1B0 */ u8 field_0x1B0[0x8]; /* InitTn copies eight bytes (D_002C41D0) here */
};

enum TNS {
    TNS_OFF = 0, /* SetTnTns revokes the camera policy */
    TNS_ON = 1   /* SetTnTns sets the camera policy */
};

#if defined(__mips__)
typedef char check_TN_psoFocus[((unsigned int)&((struct TN *)0)->psoFocus == 0xE0) ? 1 : -1];
typedef char check_TN_pcrv[((unsigned int)&((struct TN *)0)->pcrv == 0x10C) ? 1 : -1];
typedef char check_TN_pstepCurrent[((unsigned int)&((struct TN *)0)->pstepCurrent == 0x118) ? 1 : -1];
typedef char check_TN_pri[((unsigned int)&((struct TN *)0)->pri == 0x128) ? 1 : -1];
typedef char check_TN_tns[((unsigned int)&((struct TN *)0)->tns == 0x134) ? 1 : -1];
typedef char check_TN_tTns[((unsigned int)&((struct TN *)0)->tTns == 0x138) ? 1 : -1];
typedef char check_TN_tnsOverride[((unsigned int)&((struct TN *)0)->tnsOverride == 0x13C) ? 1 : -1];
#endif
#endif

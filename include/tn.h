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
    u8 unknown_0xE4[0x28];
    /* 0x10C */ struct CRV *pcrv;   /* the curve: CloneTn clones it, LoadTnFromBrx loads it, UpdateCptnClosestPoint measures on it */
    u8 unknown_0x110[0x8];
    /* 0x118 */ void *pstepCurrent; /* the current camera step: func_00221818 sets it, func_00221940 clears it */
    u8 unknown_0x11C[0xC];
    /* 0x128 */ s32 pri;            /* SetTnTns: the camera policy priority, 2 added */
    u8 unknown_0x12C[0x8];
    /* 0x134 */ s32 tns;            /* SetTnTns: the state, TNS */
    /* 0x138 */ f32 tTns;           /* SetTnTns: the time of the last state change */
    /* 0x13C */ s32 tnsOverride;    /* UpdateTn tests it; UpdateTnCallback, SetTnTnsOverride, InitTn (-1) */
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

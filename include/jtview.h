/* SPDX-License-Identifier: GPL-3.0-or-later */
/* C view of JT (jt.h), which is C++ only: the part of it that the player code written in C reads, with jt.h's names and offsets,
   as guardview.h is for STEP and STEPGUARD. The parts InitJt starts in place (jt.h's PvJmp, PvAttach, PvZap, PvVjoy) are byte
   arrays here, taken by address. A field jt.h lacks is here only, with its readers. A C++ source uses JT itself. C only. */
#ifndef SLY2_JTVIEW_H
#define SLY2_JTVIEW_H
#ifdef __cplusplus
#error "jtview.h is the C view of jt.h: include jt.h in C++"
#endif
#include "types.h"
#include "guardview.h"
#include "goals.h"

struct TN;

/* the C slice of JT */
struct JTVIEW {
    u8 unknown_0x0[0x26C];
    /* 0x26C */ struct GOALSTACK goalstack; /* STEP::pgoalstack(): GoalStack_Clear takes its address (func_00141928) */
    u8 unknown_0x274[0x4C];
    /* 0x2C0 */ u8 jmp[0x1C];               /* JT::PvJmp(): SetJmpState, func_00199298 take its address */
    /* 0x2DC */ s32 jmpState;
    u8 unknown_0x2E0[0x1E0];
    /* 0x4C0 */ u8 attach[0x8];             /* JT::PvAttach(): StartAttach takes its address */
    /* 0x4C8 */ s32 attachKind;
    u8 unknown_0x4CC[0x4F0];
    /* 0x9BC */ s32 field_0x9BC;            /* JT::field_0x9BC; func_00141D38 */
    u8 unknown_0x9C0[0x8];
    /* 0x9C8 */ s32 field_0x9C8;            /* func_001424E0 (which sets sidDefault too): the default of field_0x9CC */
    /* 0x9CC */ s32 field_0x9CC;            /* func_001424E0 */
    u8 unknown_0x9D0[0x420];
    /* 0xDF0 */ u8 zap[0x4];                /* JT::PvZap(): ZapTakeDamage, bevy_player_p7_damage_1a23c0 take its address */
    /* 0xDF4 */ s32 zapState;
    u8 unknown_0xDF8[0x104];
    /* 0xEFC */ void *pasegaHandle;         /* func_00141928 retracts it (RetractAsegaHandle) */
    u8 unknown_0xF00[0x14];
    /* 0xF14 */ void *pasegaHandle2;        /* func_00141928 retracts it after pasegaHandle */
    u8 unknown_0xF18[0xB8];
    /* 0xFD0 */ u8 vjoy[0];                 /* JT::PvVjoy(): GoalFollowCrvVjoy's Activate and Update pass it to func_001448F0 */
    u8 unknown_0xFD0[0x30];
    /* 0x1000 */ s32 field_0x1000;          /* JT::field_0x1000 (InitMurray sets 4, InitBentley 2); func_001841F0 masks it */
    u8 unknown_0x1004[0x20];
    /* 0x1024 */ struct TN *ptnOverride;    /* func_00140C88 swaps it, calling SetTnTnsOverride on the old and the new */
    u8 unknown_0x1028[0xB4];
    /* 0x10DC */ sptr field_0x10DC;         /* JT::field_0x10DC, a STEPGUARD address: func_001431D0 takes its goal stack */
    /* 0x10E0 */ s32 fFocusBusy;            /* JT::fFocusBusy: the partner attack goals' Deactivate clear bit 0 */
    u8 unknown_0x10E4[0x1C];
    /* 0x1100 */ s32 fLookHold;             /* JT::fLookHold: ReleaseJtLookHold clears it */
    u8 unknown_0x1104[0xB0];
    /* 0x11B4 */ s32 field_0x11B4;          /* JT::field_0x11B4; func_001424C0 */
    u8 unknown_0x11B8[0x160];
    /* 0x1318 */ s32 sidDefault;            /* JT::sidDefault; func_001424E0 sets it */
    u8 unknown_0x131C[0x4];
};

#if defined(__mips__)
typedef char check_JTVIEW_size[(sizeof(struct JTVIEW) == 0x1320) ? 1 : -1];
typedef char check_JTVIEW_vjoy[((unsigned int)&((struct JTVIEW *)0)->vjoy == 0xFD0) ? 1 : -1];
typedef char check_JTVIEW_fFocusBusy[((unsigned int)&((struct JTVIEW *)0)->fFocusBusy == 0x10E0) ? 1 : -1];
#endif
#endif

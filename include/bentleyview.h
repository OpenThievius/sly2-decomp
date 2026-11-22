/* SPDX-License-Identifier: GPL-3.0-or-later */
/* C view of BENTLEY (bentley.h, C++ only): the slice that Bentley's player code written in C reads, with bentley.h's names and
   offsets. The parts InitJt starts in place (JT::PvPipe at 0xF50) are byte arrays taken by address. A field bentley.h lacks is
   here only, with its readers. A C++ source uses BENTLEY itself. C only. */
#ifndef SLY2_BENTLEYVIEW_H
#define SLY2_BENTLEYVIEW_H
#ifdef __cplusplus
#error "bentleyview.h is the C view of bentley.h: include bentley.h in C++"
#endif
#include "types.h"
#include "gadgetobj.h"

struct BENTLEYSLOTVIEW {
    /* 0x0 */ s32 gadget;
    /* 0x4 */ void *ppool;
    /* 0x8 */ void *plo;
};

struct BENTLEYVIEW {
    u8 unknown_0x0[0x4CC];
    /* 0x4CC */ s32 field_0x4CC;           /* JT::field_0x4CC */
    u8 unknown_0x4D0[0xA80];
    /* 0xF50 */ u8 pipe[0x4];              /* JT::PvPipe(): func_0019EA00 takes its address */
    u8 unknown_0xF54[0x12C];
    /* 0x1080 */ f32 field_0x1080;         /* JT::field_0x1080; GetBentleyCpdefi sets it from the clock */
    u8 unknown_0x1084[0x34C];
    /* 0x13D0 */ s32 state;                /* BENTLEY::state */
    u8 unknown_0x13D4[0x2E0];
    /* 0x16B4 */ struct BENTLEYSLOTVIEW *pslotActive; /* BENTLEY::pslotActive */
    u8 unknown_0x16B8[0x4];
    /* 0x16BC */ s32 aimState;             /* BENTLEY::aimState */
    /* 0x16C0 */ f32 tAim;                 /* SetBentleyAimState sets it to the clock time when the aim state changes (one reader) */
    u8 unknown_0x16C4[0x4C];
    /* 0x1710 */ u8 lookrig[0x4];          /* the look rig InitBentley starts: SetLookRigState takes its address */
    u8 unknown_0x1714[0x158];
    /* 0x186C */ struct GADGETOBJ *ploGadget;   /* BENTLEY::ploGadget (gadgetobj.h) */
    u8 unknown_0x1870[0x10];
};

#if defined(__mips__)
typedef char check_BENTLEYVIEW_size[(sizeof(struct BENTLEYVIEW) == 0x1880) ? 1 : -1];
typedef char check_BENTLEYVIEW_state[((unsigned int)&((struct BENTLEYVIEW *)0)->state == 0x13D0) ? 1 : -1];
typedef char check_BENTLEYVIEW_ploGadget[((unsigned int)&((struct BENTLEYVIEW *)0)->ploGadget == 0x186C) ? 1 : -1];
#endif
#endif

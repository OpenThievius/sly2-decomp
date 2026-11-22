/* SPDX-License-Identifier: GPL-3.0-or-later */
/* JSG, the camera-cut sequence player (CSeq) of src/game-stepguard/ (StartJsg, StopJsg, ClearJsg, FIsJsgActive, StartJsgFocus; fun_001e0128
   and fun_001e01c8 read the same words) and src/stepguard-jsg/ (func_001E0070 removes a signal, func_001E0120 clears the list). It is
   an LO: its +0x40 is the LO's grf word and entry pointer, which StartJsg and StopJsg use as AddSwGrfEntry's union, and StartJsg and
   StopJsg call LO slot 3, HandleSpliceEvent, with five words. C++ gets the class; a C source gets the C view below (same offsets, the
   first 0x50 bytes unnamed). The records AddJsgContext_file queues are JSGE (its own local type). */
#ifndef SLY2_JSG_H
#define SLY2_JSG_H
#include "types.h"

#ifdef __cplusplus
#include "sw.h"

struct JSG : LO {
    /* 0x50 */ s32 phase;       /* ClearJsg zeroes it; fun_001e01c8 tests it (< 2) before it takes a new ajsge */
    /* 0x54 */ s32 ajsge;       /* StartJsg passes it to PseqnodeNew; fun_001e01c8 stores its argument (1 to 0x1FF) */
    u8 unknown_0x58[4];
    /* 0x5C */ DL dlSeqnode;    /* StartJsg asks FIsDlEmpty; StopJsg stops each node */
    u8 unknown_0x68[4];
    /* 0x6C */ s32 psoSubject;  /* StartJsg stores its argument, StopJsg clears it */
    /* 0x70 */ f32 tRun;        /* StopJsg zeroes it */
    /* 0x74 */ s32 fRunning;    /* FIsJsgActive, StartJsg, StopJsg */
    /* 0x78 */ s32 fLatched;    /* StartJsg sets it after taking grf bit 2; StopJsg clears that bit when it is set */
    /* 0x7C */ s32 fPendingCut; /* ClearJsg sets it; fun_001e01c8 sets it; StartJsg clears it after AddSeqRecordEndThread */
    u8 unknown_0x80[4];
#else
/* C view of the JSG above */
struct JSG {
    u8 unknown_0x0[0x74];
    /* 0x74 */ s32 fRunning;    /* JSG::fRunning */
    u8 unknown_0x78[0xC];
#endif
    /* 0x84 */ s32 csignal;     /* the signals raised and not yet cleared: func_001E0070, func_001E0120 */
    /* 0x88 */ s32 asignal[1];  /* their ids (the capacity is not known; a walk goes past [0]): func_001E0070 removes one and moves the rest down */
};

#if defined(__mips__)
typedef char check_JSG_fRunning[((unsigned int)&((struct JSG *)0)->fRunning == 0x74) ? 1 : -1];
typedef char check_JSG_csignal[((unsigned int)&((struct JSG *)0)->csignal == 0x84) ? 1 : -1];
typedef char check_JSG_asignal[((unsigned int)&((struct JSG *)0)->asignal == 0x88) ? 1 : -1];
#endif
#endif

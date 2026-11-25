/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ATTACH, the record of the player's attach step (InitAttach 0x191090 sets it up, LoadAttach 0x1910F8 loads it, StartAttach picks
   a kind and a target, FAttachGroundTarget chooses one from the world's target list, ForgetJtGuards makes the guards forget the
   player). The size is not known; the fields are those these five functions read or write. The sub-objects are named after the
   function that takes their address. C++ only. */
#ifndef SLY2_ATTACH_H
#define SLY2_ATTACH_H
#include "sly.h"
#include "sw.h"

struct TN;

struct ATTACH {
    /* 0x000 */ SLY *pjt;       /* InitAttach (its argument); every function reads it as the player */
    /* 0x004 */ f32 t;          /* StartAttach: the clock at the start */
    /* 0x008 */ s32 kind;       /* StartAttach; InitAttach sets -1 */
    /* 0x00C */ s32 field_0x0C; /* InitAttach sets -1 */
    u8 unknown_0x10[0x4];
    /* 0x014 */ LO *ptarget;    /* StartAttach: the target object (FAttachGroundTarget passes the candidate's) */
    /* 0x018 */ s32 imember;    /* StartAttach: the target's member index (func_001942F0 passes it to AddSafePointOnMember) */
    u8 unknown_0x1C[0x4];
    /* 0x020 */ f32 value;      /* func_001942F0 passes it to AddSafePointOnMember (kinds 3, 0 and 13) */
    u8 unknown_0x24[0x30];
    /* 0x054 */ void *apaseg[5]; /* PasegAttachBase (the attach's own reader): the animation segment of the kind (0: [0], or [3] for sub-kind 5; 1: [1]; 8: [4] for sub-kinds 9 and 10, the secondary one); [2] is not read there */
    /* 0x068 */ TN *ptn;        /* LoadAttach: PloNew(0xF, 0, 0x148, -1); ResetJtDynamicTunnel reads its tunnel from here */
    u8 unknown_0x6C[0x4];
    /* 0x070 */ u8 blendA[0x100]; /* LoadAttach: BuildPlainBlend's second argument, with the quadword at 0x170 */
    /* 0x170 */ QW vecBlendA;
    /* 0x180 */ u8 runA[0xC0];     /* InitAttach and LoadAttach take its address (func_0020B840, PostStepLoadRun) */
    /* 0x240 */ u8 runB[0xB0];    /* the same two functions */
    /* 0x2F0 */ u8 asegblA[0x24]; /* LoadAttach: EnsureAsegBlendDynamic's fifth argument */
    /* 0x314 */ u8 asegblB[0x1C]; /* LoadAttach: its last argument */
    /* 0x330 */ u8 blendB[0x100]; /* LoadAttach: BuildPlainBlend's second argument, with the quadword at 0x430 */
    /* 0x430 */ QW vecBlendB;
    /* 0x440 */ u8 carry[0x84];   /* InitAttach: Carry_Init; StartAttach: Carry_SetState; LoadAttach: func_001CC5E8 */
    /* 0x4C4 */ LO *carryTarget;  /* StartAttach: the target of a kind 5 or 9 attach, handed to the carry */
    u8 unknown_0x4C8[0x34];
    /* 0x4FC */ s32 field_0x4FC;  /* InitAttach sets -1 */
    /* 0x500 */ s32 noHold;       /* StartAttach: set for kinds 11 and 12 */
};

extern "C" void StartAttach(ATTACH *pattach, unsigned kind, LO *ptarget, s32 imember);
extern "C" void ForgetJtGuards(ATTACH *pattach);
#endif

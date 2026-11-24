/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SMA, an animation driven by a state machine, and SM, SMT, SMS, SMDIST, the machine itself. Retail's names (SM, SMA, SMT, ISMS,
   PsmaApplySm, IsmsFindSmRequired, SetSmaGoal__FP3SMA3OID) from its mangled symbols; field names ours, readers listed per field (the
   shdanim-sm module's functions, InitSm_file.cpp, where two or more agree). C++ for the classes; a C source reads SMA through the C
   struct (only the words two readers agree on). */
#ifndef SLY2_SMA_H
#define SLY2_SMA_H
#include "types.h"
#ifdef __cplusplus
#include "lo.h"
#include "dl.h"
#include "asega.h"

struct ALO;

/* One state of a state machine (SM::asms, 8 bytes): its object id and the state it moves on to by itself (-1 none, -2 any). */
struct SMS {
    /* 0x0 */ s32 oid;       /* IsmsFindSmOptional, OidFromSmIsms */
    /* 0x4 */ s32 ismsNext;  /* ChooseSmaTransition */
};

/* One transition (SM::asmt, 0x18 bytes). */
struct SMT {
    /* 0x00 */ struct ASEG *paseg;  /* ChooseSmaTransition: the animation that plays it */
    /* 0x04 */ s32 ismsFrom;        /* ChooseSmaTransition, PsmtChooseSmTowards, PsmtChooseSmAny */
    /* 0x08 */ s32 ismsTo;          /* same readers */
    /* 0x0C */ u32 grfsmt;          /* SetSmaGoal (bit 2), PsmtChooseSmTowards, PsmtChooseSmAny (bit 1: reversible) */
    /* 0x10 */ u32 grfsmtMask;      /* SetSmaMask tests it against the new mask (one reader: guess) */
    /* 0x14 */ f32 g;               /* PsmtChooseRandom: the weight */
};

/* A table of distances between states for the transitions a mask lets through (SM::adist, 8 bytes). */
struct SMDIST {
    /* 0x0 */ u32 grfsmt;           /* func_001F0458 matches it against the mask */
    /* 0x4 */ s8 *adist;            /* func_001F0498: cisms * cisms bytes */
};

/* What SM::pinit points at (func_001F0128 allocates and fills it, PostSmLoad reads it). */
struct SMINIT {
    /* 0x0 */ s32 oidRoot;          /* PostSmLoad: the object it looks up */
    /* 0x4 */ s32 oidInitial;
    /* 0x8 */ s32 grfapl;
};

struct SM : LO {
    /* 0x50 */ s32 cisms;           /* IsmsFindSmOptional, OidFromSmIsms, func_001F0498 */
    /* 0x54 */ SMS *asms;           /* IsmsFindSmOptional, OidFromSmIsms, ChooseSmaTransition */
    /* 0x58 */ s32 csmt;            /* PsmtChooseSmTowards, PsmtChooseSmAny */
    /* 0x5C */ SMT *asmt;           /* same */
    /* 0x60 */ s32 cdist;           /* func_001F0458 */
    /* 0x64 */ SMDIST *adist;       /* func_001F0458 */
    /* 0x68 */ DL dlsma;            /* PsmaFindSm walks it, PsmaApplySmInternal and RetractSma enter and remove SMAs */
    /* 0x74 */ SMINIT *pinit;       /* PostSmLoad, func_001F0128 */
};

struct SMA : BASIC {
    /* 0x10 */ s32 cref;            /* Sma_AddRef, Sma_Release */
    /* 0x14 */ struct SMA *psmaNext; /* the DLE in SM::dlsma: PsmaFindSm follows it */
    u8 unknown_0x18[0xC];
    /* 0x24 */ SM *psm;
    /* 0x28 */ struct ALO *paloRoot;
    /* 0x2C */ s32 grfapl;
    /* 0x30 */ ASEGA *pasega;       /* the playing transition: SetSmaGoal, SeekSma, SnapSmaTransition, ChooseSmaTransition; HandleSmaMessage compares it */
    /* 0x34 */ s32 ismsCur;
    /* 0x38 */ s32 ismsNext;
    /* 0x3C */ s32 ismsGoal;
    /* 0x40 */ SMT *psmt;
    /* 0x44 */ f32 svt;
    /* 0x48 */ u32 grfsmt;          /* the mask PsmaApplySmInternal stores, SetSmaMask changes */
    u8 unknown_0x4C[0x4];
};
#else

struct SM;
struct ASEGA;

struct SMA {
    u8 unknown_0x0[0x24];
    /* 0x24 */ struct SM *psm;       /* SetSmaGoalIfReachable (IsmsFindSmOptional, PsmtChooseSmTowards), func_001D14C0 (the goal it snaps to) */
    u8 unknown_0x28[0x8];
    /* 0x30 */ struct ASEGA *pasega; /* SetSmaGoalIfReachable tests it; RenderDprizeAll asks PchnFindAseg for it */
};
#endif
#endif

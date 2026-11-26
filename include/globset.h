/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GLOBSET, the globset an SO embeds at 0x80 (so.h field_0x80: func_001F3CC8 and CSo_LoadFromBrx pass its address). Only its
   constructor is known: GLOBSET::GLOBSET (0x167310, mangled __7GLOBSET) sets the word at 0x4C to -1 and returns its argument;
   the inlined constructor chains of SO-derived classes call it out of line (the factories of new_100008, ConstructGuard,
   ConstructSly, ConstructMurray, func_00112100). Its real size is not known: the struct below holds the known part only, so a
   view that reaches past it (0x174 of an SO-derived instance) pads with unknown_0xOFF arrays after it. C and C++. */
#ifndef SLY2_GLOBSET_H
#define SLY2_GLOBSET_H
#include "types.h"

struct ALO;
struct GLOBREC;
struct GLOBINFO;

/* one glob's bound, 0x18 bytes each (GLOBSET::asubglob): LoadGlobsetFromBrx reads it from the stream (the center, then the radius, a
   word and a distance that defaults by the glob's type); func_0016EF00 resets one to the world center with radius 1e6 */
typedef struct SUBGLOB {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 radius;
    /* 0x10 */ f32 field_0x10;     /* LoadGlobsetFromBrx: 1e10 or 2000 by the glob's type when the stream holds FLT_MAX */
    /* 0x14 */ u32 field_0x14;     /* LoadGlobsetFromBrx (U32Read) */
} SUBGLOB;

typedef struct GLOBSET {
    /* 0x00 */ struct ALO *palo;   /* its owner: LoadGlobsetFromBrx stores it (and asks it for transforms through SO slot 51), func_0016EF00
                                      takes it out of the render tree (RemoveAloFromRenderTree) */
    u8 unknown_0x4[0xC];
    /* 0x10 */ f32 center[3];      /* LoadGlobsetFromBrx (ReadVector), func_0016EF00 (copies the world center in as a quadword: the word at
                                      0x1C goes with it). Not a VECTOR: that would make GLOBSET 16-aligned, and the factories (factory.h)
                                      embed it at 8-aligned offsets */
    u8 unknown_0x1C[0x4];
    /* 0x20 */ f32 radius;         /* LoadGlobsetFromBrx (F32Read), func_0016EF00 (1e6) */
    /* 0x24 */ s32 field_0x24;     /* LoadGlobsetFromBrx: the count of the ids at field_0x28 */
    /* 0x28 */ s32 *field_0x28;    /* the ids (func_001ED7A8's results) */
    /* 0x2C */ s32 field_0x2C;     /* a count: LoadGlobsetFromBrx */
    /* 0x30 */ s32 *field_0x30;    /* its words (S32Read) */
    /* 0x34 */ s32 field_0x34;     /* LoadGlobsetFromBrx sets 0 */
    /* 0x38 */ s32 cglob;          /* LoadGlobsetFromBrx (S16Read; a skipped glob lowers it) */
    /* 0x3C */ struct GLOBREC *aglob;   /* 0x14 bytes each: LoadGlobsetFromBrx and LoadGlobsetBndTreeFromBrx (its own view calls it asubglobi) */
    /* 0x40 */ struct GLOBINFO *aglobi; /* 0x28 bytes each: the same two (the second's view calls it asubglob) */
    /* 0x44 */ SUBGLOB *asubglob;  /* LoadGlobsetFromBrx allocates it unless the record says there are none; func_0016EF00 indexes it */
    /* 0x48 */ void *abndnode;     /* LoadGlobsetBndTreeFromBrx */
    /* 0x4C */ s32 field_0x4C; /* GLOBSET::GLOBSET sets it to -1 */
#ifdef __cplusplus
    GLOBSET();
#endif
} GLOBSET;

/* GLOBSET::GLOBSET called by its symbol (C callers, ConstructGuard): constructs the globset at pglobset and returns it */
#ifdef __cplusplus
extern "C" GLOBSET *__7GLOBSET(GLOBSET *pglobset);
#else
GLOBSET *__7GLOBSET(GLOBSET *pglobset);
#endif

#endif

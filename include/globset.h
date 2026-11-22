/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GLOBSET, the globset an SO embeds at 0x80 (so.h field_0x80: func_001F3CC8 and CSo_LoadFromBrx pass its address). Only its
   constructor is known: GLOBSET::GLOBSET (0x167310, mangled __7GLOBSET) sets the word at 0x4C to -1 and returns its argument;
   the inlined constructor chains of SO-derived classes call it out of line (the factories of new_100008, ConstructGuard,
   ConstructSly, ConstructMurray, func_00112100). Its real size is not known: the struct below holds the known part only, so a
   view that reaches past it (0x174 of an SO-derived instance) pads with unknown_0xOFF arrays after it. C and C++. */
#ifndef SLY2_GLOBSET_H
#define SLY2_GLOBSET_H
#include "types.h"

typedef struct GLOBSET {
    u8 unknown_0x0[0x4C];
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

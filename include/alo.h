/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ALO, an animated object: derived from SO (so.h); retail's slot 51 of SO is PxfFromAloRef and slot 18 UpdateAloXfWorldHierarchy.
   C++ derives it from SO; a C source (which cannot include so.h) reads the part it needs through the C struct with the same
   offsets. Fields: EnsureAloSfx (sfx, the sound block, tested at its 0x108), PxfFromAloRef and FUN_0012a860 (psoParent). */
#ifndef SLY2_ALO_H
#define SLY2_ALO_H
#ifdef __cplusplus
#include "lo.h"
#include "so.h"
#else
#include "types.h"
#endif

struct ALOSFX {
    u8 unknown_0x0[0x108];
    /* 0x108 */ s32 field_0x108; /* EnsureAloSfx: the block is initialised (func_001CC2E8) while it is 0 */
};

#ifdef __cplusplus
struct ALO : SO {
    u8 unknown_0x150[0x150];
    /* 0x2A0 */ s32 arefSmKind[6]; /* RetainAloSmKinds, ReleaseAloSmKinds (they agree): how many users hold each of the six SM kinds */
    u8 unknown_0x2B8[0x1518];
    /* 0x17D0 */ ALOSFX sfx;
};
#else
struct SO;
struct ALO {
    u8 unknown_0x0[0x10];
    /* 0x10 */ struct SO *psoParent;
    u8 unknown_0x14[0x17BC];
    /* 0x17D0 */ struct ALOSFX sfx;
};
#endif
#endif

/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SHDFRAMES, the 0x1C-byte record func_001EB678 builds for each shader with flag 0x40 (LoadShadersFromBrx allocates it, calls
   func_001EB678 and appends it to the list at B_003E1590; PshdframesFromOid walks that list by oid). C++ only. */
#ifndef SLY2_SHDFRAMES_H
#define SLY2_SHDFRAMES_H
#include "types.h"
#include "rgba.h"

struct SHDFRAMES {
    /* 0x00 */ s32 oid;                 /* func_001EB678 copies SHD::oid; PshdframesFromOid matches it */
    /* 0x04 */ s32 field_0x6;           /* func_001EB678 copies SHD::field_0x6 */
    /* 0x08 */ s32 grf;                 /* func_001EB678 copies SHD::grf */
    /* 0x0C */ RGBA rgba8;              /* func_001EB678 copies SHD::rgba8 */
    /* 0x10 */ s32 cframe;              /* func_001EB678: the first texture's cbmp */
    /* 0x14 */ s64 *aframe;             /* func_001EB678 allocates cframe entries and fills them with func_001EA6C8's results */
    /* 0x18 */ struct SHDFRAMES *next;  /* the list link (AppendSlEntry, ibSle 0x18); PshdframesFromOid follows it */
};

#if defined(__mips__)
typedef char check_SHDFRAMES_size[(sizeof(struct SHDFRAMES) == 0x1C) ? 1 : -1];
#endif
#endif

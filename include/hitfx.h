/* SPDX-License-Identifier: GPL-3.0-or-later */
/* HITFX, a hit effect (slot heap 0x3E1498; the list at 0x3E148C holds the live ones): a BASIC (vtable at 0xC; slot 1 and 2
   are its AddRef and Release, slot 3 and 4 the splice event and the message HitFx_Remove sends) with a reference count at 0x10.
   In C the BASIC's 0x10 bytes are unknown. Readers: HitFx_AddRef, HitFx_Release (cRef), HitFx_CheckExpiry and HitFx_GIntensity
   (pdef, tStart: both agree on 0x14 and 0x4C). HITFXDEF is the effect's definition record. */
#ifndef SLY2_HITFX_H
#define SLY2_HITFX_H
#include "types.h"
#ifdef __cplusplus
#include "lo.h"
#endif

/* HITFXDEF, an effect's definition: a class 0x75 object (InitSwHitFxParms makes seven with PloNew and calls slot 9, Remove, on each),
   so an LO in C++; in C the LO's 0x50 bytes are unknown. */
#ifdef __cplusplus
struct HITFXDEF : LO {
#else
struct HITFXDEF {
    u8 unknown_0x0[0x50];
#endif
    /* 0x50 */ s32 fSense;      /* InitSwHitFxParms sets 0 or 1; func_001CBEE0 (the guard class's slot-89 override) widens the range only while it is 0 */
    /* 0x54 */ f32 strength;    /* InitSwHitFxParms sets it for four definitions; func_001CBEE0 doubles it with the range and restores it */
    u8 unknown_0x58[0x8];
    /* 0x60 */ f32 duration;    /* HitFx_CheckExpiry (below 0: never expires), HitFx_GIntensity; InitSwHitFxParms sets it */
};

#ifdef __cplusplus
struct HITFX : BASIC {
#else
struct HITFX {
    u8 unknown_0x0[0x10];
#endif
    /* 0x10 */ s32 cRef;        /* HitFx_AddRef, HitFx_Release */
    /* 0x14 */ struct HITFXDEF *pdef; /* HitFx_CheckExpiry, HitFx_GIntensity */
    u8 unknown_0x18[0x2C];
    /* 0x44 */ struct LO *source; /* func_00208BE0 (guard slot 89) and PhitfxChooseForGuard (they agree): the object that caused it; the key of the guard's SENSOR entry */
    u8 unknown_0x48[0x4];
    /* 0x4C */ f32 tStart;      /* HitFx_CheckExpiry, HitFx_GIntensity */
    u8 unknown_0x50[0x4];
    /* 0x54 */ s32 level;       /* func_00208BE0 compares it with the guard's field_0xE68, PhitfxChooseForGuard tests 4 */
    /* 0x58 */ struct HITFX *pnext; /* PhitfxChooseForGuard walks the live list (B_003E148C) through it */
};
#endif

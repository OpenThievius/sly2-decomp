/* SPDX-License-Identifier: GPL-3.0-or-later */
/* C view of SW (sw.h), which is C++ only: the part of the world that the sources written in C read, with sw.h's names and
   offsets (the *Sw* functions take the world as their first argument, so the class is certain). A field sw.h lacks is here only,
   with its readers. A C++ source uses SW itself. C only. */
#ifndef SLY2_SWVIEW_H
#define SLY2_SWVIEW_H
#ifdef __cplusplus
#error "swview.h is the C view of sw.h: include sw.h in C++"
#endif
#include "types.h"
#include "dcb.h"

struct PO;
struct CB;

struct SWVIEW {
    u8 unknown_0x0[0x39D0];
    /* 0x39D0 */ struct DCB *adcb;       /* SW::adcb: PdcbAllocSw hands out from it */
    /* 0x39D4 */ s32 cdcb;               /* SW::cdcb: PdcbAllocSw */
    /* 0x39D8 */ struct OPTSET *aoptset; /* SW::aoptset: func_00210120 hands out from it */
    /* 0x39DC */ s32 coptset;            /* SW::coptset: func_00210120 */
    u8 unknown_0x39E0[0x2C8];
    /* 0x3CA8 */ struct CB *pcbFirst;    /* SW::pcbFirst: the queued callbacks, QueueSwCallbackOnce walks them through CB::pnext */
    u8 unknown_0x3CAC[0xCC];
    /* 0x3D78 */ s32 chandsOff;          /* SW::chandsOff: FSwHandsOff tests it > 0 */
    /* 0x3D7C */ s32 chandsOffSw;        /* SW::chandsOffSw: IncrementSwHandsOff, DecrementSwHandsOff */
    /* 0x3D80 */ s32 cshow;     /* IncrementSwShowCount, DecrementSwShowCount */
    /* 0x3D84 */ s32 cbinoc;    /* IncrementSwBinocCount, DecrementSwBinocCount, FSwBinocActive */
    u8 unknown_0x3D88[0x88];
    /* 0x3E10 */ QW hsvFog;     /* SetSwFogHsv */
    /* 0x3E20 */ f32 scaleFog;  /* func_0020F2F8 */
    /* 0x3E24 */ f32 alphaFog;  /* func_0020F2D8 */
    u8 unknown_0x3E28[0xD4];
    /* 0x3EFC */ struct PO *ppoFocusBase;     /* PpoSwFocusBase returns it (SetSwFocusBase writes it) */
    /* 0x3F00 */ struct PO *ppoFocusOverride; /* PpoSwFocus returns it when it is not null, else the base (SetSwFocusOverride) */
};

#if defined(__mips__)
typedef char check_SWVIEW_adcb[((unsigned int)&((struct SWVIEW *)0)->adcb == 0x39D0) ? 1 : -1];
typedef char check_SWVIEW_pcbFirst[((unsigned int)&((struct SWVIEW *)0)->pcbFirst == 0x3CA8) ? 1 : -1];
typedef char check_SWVIEW_chandsOff[((unsigned int)&((struct SWVIEW *)0)->chandsOff == 0x3D78) ? 1 : -1];
typedef char check_SWVIEW_cshow[((unsigned int)&((struct SWVIEW *)0)->cshow == 0x3D80) ? 1 : -1];
typedef char check_SWVIEW_hsvFog[((unsigned int)&((struct SWVIEW *)0)->hsvFog == 0x3E10) ? 1 : -1];
typedef char check_SWVIEW_ppoFocusBase[((unsigned int)&((struct SWVIEW *)0)->ppoFocusBase == 0x3EFC) ? 1 : -1];
#endif
#endif

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

struct PO;

struct SWVIEW {
    u8 unknown_0x0[0x3D80];
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
typedef char check_SWVIEW_hsvFog[((unsigned int)&((struct SWVIEW *)0)->hsvFog == 0x3E10) ? 1 : -1];
typedef char check_SWVIEW_ppoFocusBase[((unsigned int)&((struct SWVIEW *)0)->ppoFocusBase == 0x3EFC) ? 1 : -1];
#endif
#endif

/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ROPESIM, the rope simulation of a curve (PattachCrv makes it, ConstructRopeSim fills it; CRV::pattach points at it). Only the fields
   two readers agree on are declared: each source used to declare its own view of the object (ConstructRopeSim, RemeasureRopeSim,
   func_001E6340, func_001E7FF0, func_001E79A0). The size is not known. C++ only. */
#ifndef SLY2_ROPESIM_H
#define SLY2_ROPESIM_H
#include "types.h"
#include "crv.h"

struct ROPESIM {
    u8 unknown_0x0[0x48];
    /* 0x48 */ struct CRV *pcrv;  /* ConstructRopeSim stores it; RemeasureRopeSim reads its control points */
    /* 0x4C */ s32 mode;          /* ConstructRopeSim sets -1; func_001E6340, func_001E7FF0 (SetCrvRopeMode's getter) */
    u8 unknown_0x50[0x4];
    /* 0x54 */ QW *apos;          /* ConstructRopeSim allocates it (ccv quadwords) */
    /* 0x58 */ QW *avel;          /* ConstructRopeSim allocates it */
    /* 0x5C */ f32 *as;           /* ConstructRopeSim (the cumulative lengths); func_001E79A0; RemeasureRopeSim copies the curve's into it */
};
#endif

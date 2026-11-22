/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CRV, a curve (the object InitCrv, CloneCrv, MeasureCrv work on): an LO subclass (ConstructRopeSim calls its slot 31, LO's
   PmatWorld). Fields: ccv (the control-point count: ConstructRopeSim, func_0017C3E8, func_00155AE0) and apos (the point array: the
   same three, plus func_0014AA30). C and C++. */
#ifndef SLY2_CRV_H
#define SLY2_CRV_H
#include "types.h"
#ifdef __cplusplus
#include "lo.h"
struct CRV : LO {
    u8 unknown_0x50[0x98];
#else
struct CRV {
    u8 unknown_0x0[0xE8];
#endif
    /* 0xE8 */ s32 ccv;
    u8 unknown_0xEC[0x8];
    /* 0xF4 */ QW *apos;
};
#endif

/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CRV, a curve (the object InitCrv, CloneCrv, MeasureCrv work on): class 10 of retail's class table (0x190 bytes), an LO subclass
   (ConstructRopeSim calls its slot 31, LO's PmatWorld). Fields: crvk (the kind: FindCrvClosestPointFromU, LoadCrvFromBrx, SFromCrvU,
   UFromCrvS), closed (func_001CBA68, func_001CBAC0, UWrapCrv; pzo_hide.h's AttachCrv_FGetWrapRange and AttachCrv_GetParam read the same
   word), ccv (the control-point count: ConstructRopeSim, func_0017C3E8, func_00155AE0), au and as (the u and s of each control point:
   UMinCrv, UMaxCrv, UWrapCrv; SMinCrv, SMaxCrv), apos (the point array: the same three as ccv, plus func_0014AA30), field_0x148 and
   icvHint (InitCrv and InvalidateCrvCache both write them), pattach (PattachCrv makes it, CloneCrv drops it, func_001E6340
   updates it). InitCrv, UWrapCrv and the other readers named here are methods of the curve. C and C++. */
#ifndef SLY2_CRV_H
#define SLY2_CRV_H
#include "types.h"

struct ROPESIM;
#ifdef __cplusplus
#include "lo.h"
struct CRV : LO {
    u8 unknown_0x50[0x10];
    /* 0x60 */ f32 mat[16];      /* PcrvNew (the constructor) sets it to the identity: the curve's own matrix (the name is a guess) */
    u8 unknown_0xA0[0x40];
#else
struct CRV {
    u8 unknown_0x0[0xE0];
#endif
    /* 0xE0 */ s32 crvk;         /* the kind: 0 for a line (CRVL), else a curve (CRVC) */
    /* 0xE4 */ s32 closed;       /* nonzero for a closed curve: UWrapCrv wraps a parameter into [au[0], au[ccv - 1]]; func_001CBA68 has
                                    no wrap range at 0; func_001CBAC0 clamps the arc length when open */
    /* 0xE8 */ s32 ccv;
    /* 0xEC */ f32 *au;          /* UMinCrv reads the first, UMaxCrv the last, UWrapCrv both */
    /* 0xF0 */ f32 *as;          /* SMinCrv reads the first, SMaxCrv the last */
    /* 0xF4 */ QW *apos;
    u8 unknown_0xF8[0x48];
    /* 0x140 */ QW *field_0x140; /* LoadCrvFromBrx allocates and reads ccv vectors into it when crvk is not 0 */
    /* 0x144 */ QW *field_0x144; /* the same: the second array */
    /* 0x148 */ s32 field_0x148; /* InitCrv and InvalidateCrvCache set -1 */
    /* 0x14C */ f32 mpisamps[11]; /* the cache FillCrvcCache fills for a curve segment: SFromCrvU and UFromCrvS read the arc-length samples (11 of 0x2C bytes, agreed by the two readers) */
    /* 0x178 */ s32 icvHint;     /* the last segment found: IcvFindCrvS and IcvFindCrvU read and write it; InitCrv sets 1, InvalidateCrvCache 0 */
    /* 0x17C */ struct ROPESIM *pattach; /* the rope simulation PattachCrv makes; CloneCrv drops it, func_001E6340 updates it */
};

#if defined(__mips__)
typedef char check_CRV_crvk[((unsigned int)&((struct CRV *)0)->crvk == 0xE0) ? 1 : -1];
typedef char check_CRV_ccv[((unsigned int)&((struct CRV *)0)->ccv == 0xE8) ? 1 : -1];
typedef char check_CRV_pattach[((unsigned int)&((struct CRV *)0)->pattach == 0x17C) ? 1 : -1];
#endif
#endif

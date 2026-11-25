// SPDX-License-Identifier: GPL-3.0-or-later
#include "crv.h"
extern "C" void *__builtin_new(unsigned);
extern "C" void *ConstructRopeSim(void *, CRV *);
extern "C" void MeasureCrv(CRV *);
extern "C" void func_001A6CA8(CRV *, int);

static inline void ClearGrf(CRV *pcrv, unsigned mask)
{
    unsigned tagged = pcrv->grfSw;
    if (((tagged ^ 1) & 1) != 0) {
        unsigned *pu = (unsigned *)tagged;
        *pu = *pu & ~mask;
    } else {
        pcrv->grfSw = tagged & ~mask;
    }
}
static inline void SetGrf(CRV *pcrv, unsigned mask)
{
    unsigned tagged = pcrv->grfSw;
    if (((tagged ^ 1) & 1) != 0) {
        unsigned *pu = (unsigned *)tagged;
        *pu = *pu | mask;
    } else {
        pcrv->grfSw = tagged | mask;
    }
}

extern "C" void *PattachCrv(CRV *pcrv, int n)
{
    if (pcrv->pattach == 0) {
        void *pnew = __builtin_new(0x90);
        pcrv->pattach = (ROPESIM *)ConstructRopeSim(pnew, pcrv);
        MeasureCrv(pcrv);
        func_001A6CA8(pcrv, 0);
        ClearGrf(pcrv, 0x20);
        SetGrf(pcrv, 0xC);
    } else if (n == 1) {
        func_001A6CA8(pcrv, 0);
        SetGrf(pcrv, 4);
    }
    return pcrv->pattach;
}

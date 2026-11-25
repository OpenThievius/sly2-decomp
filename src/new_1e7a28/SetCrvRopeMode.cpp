// SPDX-License-Identifier: GPL-3.0-or-later
#include "crv.h"
struct ROPESIM { u8 unknown_0x0[0x4C]; s32 nMode; };
extern "C" void *PattachCrv(CRV *, int);
extern "C" void func_001A6CA8(CRV *, int);

static inline void SetFlags(CRV *pcrv, unsigned mask)
{
    if (((pcrv->grfSw ^ 1) & 1) != 0)
        *(unsigned *)pcrv->grfSw |= mask;
    else
        pcrv->grfSw |= mask;
}

static inline void ClearFlags(CRV *pcrv, unsigned mask)
{
    if (((pcrv->grfSw ^ 1) & 1) != 0)
        *(unsigned *)pcrv->grfSw &= ~mask;
    else
        pcrv->grfSw &= ~mask;
}

extern "C" void SetCrvRopeMode(CRV *pcrv, int nMode)
{
    if (nMode != -1) {
        PattachCrv(pcrv, 1);
        func_001A6CA8(pcrv, 0);
        ClearFlags(pcrv, 0x20u);
        SetFlags(pcrv, 0xCu);
    } else {
        func_001A6CA8(pcrv, 0);
        SetFlags(pcrv, 0x20u);
        ClearFlags(pcrv, 0xCu);
    }
    if (pcrv->pattach != 0)
        pcrv->pattach->nMode = nMode;
}

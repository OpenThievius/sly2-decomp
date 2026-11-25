// SPDX-License-Identifier: GPL-3.0-or-later
#include "crv.h"
extern "C" float SWrapCrv(CRV *, float);

// The forward search has its own counter (`icvNext`) and the backward branch is a plain `else`; reusing `icv` for both loops swapped $v0
// and $v1 on the `ccv - 1` / `slt` pair.
extern "C" int IcvFindCrvS(CRV *pcrv, float s, float *pds, float *pdsSeg)
{
    s = SWrapCrv(pcrv, s);
    int icv = pcrv->icvHint;
    if (pcrv->as[icv] < s) {
        int icvNext;
        for (icvNext = icv; icvNext < pcrv->ccv - 1; icvNext++) {
            if (s < pcrv->as[icvNext])
                break;
        }
        icv = icvNext - 1;
    } else {
        while (icv > 0) {
            if (!(s < pcrv->as[icv]))
                break;
            icv--;
        }
    }
    if (pds != 0)
        *pds = s - pcrv->as[icv];
    if (pdsSeg != 0)
        *pdsSeg = pcrv->as[icv + 1] - pcrv->as[icv];
    pcrv->icvHint = icv;
    return icv;
}

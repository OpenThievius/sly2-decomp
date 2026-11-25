// SPDX-License-Identifier: GPL-3.0-or-later
#include "crv.h"
extern "C" int IcvFindCrvS(CRV *, float, float *, float *);
extern "C" void FillCrvcCache(CRV *, int);

extern "C" float UFromCrvS(CRV *pcrv, float s)
{
    float ds;
    float dsSeg;
    float t;
    int icv = IcvFindCrvS(pcrv, s, &ds, &dsSeg);
    if (pcrv->crvk == 0) {
        float u = ds / dsSeg;
        t = (1.0f - u) * pcrv->au[icv] + u * pcrv->au[icv + 1];
    } else {
        FillCrvcCache(pcrv, icv);
        int isamp;
        for (isamp = 1; isamp < 10; isamp++) {
            if (ds < pcrv->mpisamps[isamp])
                break;
        }
        isamp--;
        float lo = pcrv->mpisamps[isamp];
        float hi = pcrv->mpisamps[isamp + 1];
        t = (ds - lo) / (hi - lo);
        t = ((float)isamp + t) * 0.1f;
        t = (1.0f - t) * pcrv->au[icv] + t * pcrv->au[icv + 1];
    }
    return t;
}

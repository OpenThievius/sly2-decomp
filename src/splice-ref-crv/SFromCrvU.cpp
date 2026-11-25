// SPDX-License-Identifier: GPL-3.0-or-later
#include "crv.h"
extern "C" int IcvFindCrvU(CRV *, float, float *, float *);
extern "C" void FillCrvcCache(CRV *, int);

extern "C" float SFromCrvU(CRV *pcrv, float u)
{
    float du;
    float duSeg;
    int icv = IcvFindCrvU(pcrv, u, &du, &duSeg);
    float result;
    if (pcrv->crvk == 0) {
        float t = du / duSeg;
        result = (1.0f - t) * pcrv->as[icv] + t * pcrv->as[icv + 1];
    } else {
        FillCrvcCache(pcrv, icv);
        float gSample = du * 10.0f / duSeg;
        int isamp = (int)gSample;
        float t = gSample - (float)isamp;
        float s0 = pcrv->mpisamps[isamp];
        float s1 = pcrv->mpisamps[isamp + 1];
        result = (1.0f - t) * s0 + t * s1;
        result += pcrv->as[icv];
    }
    return result;
}

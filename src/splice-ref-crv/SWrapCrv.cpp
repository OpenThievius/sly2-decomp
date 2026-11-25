#include "crv.h"
extern "C" float GModPositive__Fff(float, float);
extern "C" float SWrapCrv(CRV *crv, float s)
{
    if (crv->closed == 0)
        return s;
    float last = crv->as[crv->ccv - 1];
    if (0.0f <= s) {
        if (s <= last)
            return s;
    }
    return GModPositive__Fff(s, last);
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "crv.h"
extern "C" {
f32 GModPositive__Fff(f32, f32);

f32 UWrapCrv(CRV *crv, f32 u) {
    if (crv->closed != 0) {
        f32 uMin = crv->au[0];
        f32 uMax = crv->au[crv->ccv - 1];
        if (uMin <= u && u <= uMax) {
        } else {
            u = uMin + GModPositive__Fff(u - uMin, uMax - uMin);
        }
    }
    return u;
}

}

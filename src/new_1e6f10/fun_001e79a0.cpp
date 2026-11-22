// SPDX-License-Identifier: GPL-3.0-or-later
#include "crv.h"
// The rope simulation PattachCrv attaches; ConstructRopeSim stores the curve's cumulative lengths at 0x5C (ROPESIM::as).
struct ROPESIM {
    u8 unknown_0x0[0x5C];
    /* 0x5C */ f32 *as;
};
extern "C" {
ROPESIM *PattachCrv(CRV *pcrv, s32 n);

f32 func_001E79A0(CRV *pcrv) {
    f32 result;
    if (pcrv->ccv > 0) {
        { result = PattachCrv(pcrv, 0)->as[pcrv->ccv - 1]; goto done; }
    }
    { result = 0.0f; goto done; }
done:
    return result;
}

}

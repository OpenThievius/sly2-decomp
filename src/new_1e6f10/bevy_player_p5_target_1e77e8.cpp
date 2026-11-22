// SPDX-License-Identifier: GPL-3.0-or-later
#include "crv.h"
extern "C" {
f32 UMaxCrv(CRV *pcrv);
f32 UMinCrv(CRV *pcrv);

f32 bevy_player_p5_target_1e77e8(CRV *pcrv) {
    f32 uMax = UMaxCrv(pcrv);
    return (uMax - UMinCrv(pcrv)) / ((f32) pcrv->ccv * 10.0f);
}

}

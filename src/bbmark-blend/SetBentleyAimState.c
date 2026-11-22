/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "bentleyview.h"
#include "clock.h"

void SetLookRigState(void *plookrig, s32 state);

void SetBentleyAimState(struct BENTLEYVIEW *pbentley, s32 aimState) {
    if (aimState != pbentley->aimState) {
        pbentley->aimState = aimState;
        pbentley->tAim = (f32) g_2dded0.t;
        if (aimState == 0) {
            SetLookRigState(pbentley->lookrig, -1);
        }
    }
}

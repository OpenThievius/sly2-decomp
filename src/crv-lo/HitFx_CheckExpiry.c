/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "hitfx.h"
#include "clock.h"

void HitFx_Remove(struct HITFX *pfx);

void HitFx_CheckExpiry(struct HITFX *pfx)
{
    f32 duration;

    duration = pfx->pdef->duration;
    if (duration >= 0.0f) {
        if ((pfx->tStart + duration) < g_2dded0.t) {
            HitFx_Remove(pfx);
        }
    }
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "rip.h"
#include "clock.h"
extern "C" void RemoveRip(RIP *rip);

void UpdateRip(RIP *rip, float dt)
{
    if (rip->dtLifetime < g_2dded0.t - rip->tStart) {
        RemoveRip(rip);
        return;
    }
    if (rip->pripg->kind == 1)
        return;
    SO *touch = rip->psoTouch;
    if (touch == 0)
        return;
    if (touch->pphys == 0)
        return;
    int touching = 0;
    if ((int)(touch->grfo >> 60) & 1) {
        if (touch->Slot73(rip->pos) != 0)
            touching = 1;
    }
    rip->Touch(touching);
}

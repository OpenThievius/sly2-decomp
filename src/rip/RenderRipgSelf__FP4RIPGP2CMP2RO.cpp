// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "rip.h"
#include "clock.h"
struct CM;
struct RO;

extern "C" void RenderRipgSelf__FP4RIPGP2CMP2RO(RIPG *ripg, CM *cm, RO *ro)
{
    DLI iterator;
    PushDli(&iterator, &ripg->rips);
    for (RIP *rip = (RIP *)PvStep(&iterator); rip != 0; rip = (RIP *)PvStep(&iterator)) {
        float limit = g_2dded0.t;
        float tStart = rip->tStart;
        if (limit <= tStart) {
        } else
            rip->Slot6();
    }
    PopDli(&iterator);
}

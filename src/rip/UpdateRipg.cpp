// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "rip.h"
#include "clock.h"
extern "C" int FIsLoInWorld(LO *);
extern "C" int FIsDlEmpty__FP2DL(DL *);
extern "C" void BounceRipgRips__FP4RIPG(RIPG *);
extern "C" void AddRipRef__FP3RIP(RIP *);
extern "C" void ReleaseRip(RIP *);

extern "C" void UpdateRipg__FP4RIPG(RIPG *ripg)
{
    DLI iterator;
    PushDli(&iterator, &ripg->rips);
    for (RIP *rip = (RIP *)PvStep(&iterator); rip != 0; rip = (RIP *)PvStep(&iterator)) {
        float limit = g_2dded0.t;
        float tStart = rip->tStart;
        if (limit <= tStart) {
        } else {
            AddRipRef__FP3RIP(rip);
            rip->Update();
            ReleaseRip(rip);
        }
    }
    if (FIsLoInWorld(ripg) == 0 || FIsDlEmpty__FP2DL(&ripg->rips) != 0)
        ripg->Remove();
    else
        BounceRipgRips__FP4RIPG(ripg);
    PopDli(&iterator);
}

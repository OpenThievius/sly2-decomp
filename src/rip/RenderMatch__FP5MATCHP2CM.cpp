// SPDX-License-Identifier: GPL-3.0-or-later
#include "rip.h"
#include "clock.h"
struct CM;
extern "C" void RenderRip(RIP *rip);
extern "C" void RenderMatch__FP5MATCHP2CM(RIP *match, CM *cm)
{
    float limit = g_2dded0.t;
    float value = match->tStart;
    if (limit < value)
        return;
    RenderRip(match);
}

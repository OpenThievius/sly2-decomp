/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "rip.h"
#include "clock.h"

void ForceRipFade__FP3RIPf(struct RIP *rip, float limit) {
    float duration = rip->dtLifetime;
    float remaining = duration - (g_2dded0.t - rip->tStart);
    if (limit < remaining) {
        float ratio = remaining / duration;
        float scaled = limit / ratio;
        rip->dtLifetime = scaled;
        rip->tStart = g_2dded0.t - ((1.0f - ratio) * scaled);
    }
}

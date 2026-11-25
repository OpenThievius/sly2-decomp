#include "types.h"
// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
struct MATCH { u8 unknown_0x0[0x14]; float tCreated; float dtLifetime; LO *plo; u8 unknown_0x20[0xE4]; int paloLaunch; };
struct RIP;
void LaunchMatch(MATCH *);
extern "C" {
extern float g_2dded0;
void RemoveRip(RIP *);
}

void UpdateMatch(MATCH *pmatch, float dt)
{
    float now = g_2dded0;
    float tCreated = pmatch->tCreated;
    if (tCreated <= now && pmatch->paloLaunch != 0)
        LaunchMatch(pmatch);
    if (pmatch->dtLifetime < g_2dded0 - pmatch->tCreated) {
        pmatch->plo->Add();
        RemoveRip((RIP *)pmatch);
    }
}

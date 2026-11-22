// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
struct MATCH { char pad[0x14]; float tCreated; float dtLifetime; LO *plo; char pad2[0x104 - 0x20]; int paloLaunch; };
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

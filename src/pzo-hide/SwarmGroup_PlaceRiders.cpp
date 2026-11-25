#include "types.h"
// SPDX-License-Identifier: GPL-3.0-or-later
struct RIDER { u8 unknown_0x0[0x24]; int state; u8 unknown_0x28[0x14]; float s; float v; u8 unknown_0x44[8]; int hp; u8 unknown_0x50[0x10]; RIDER *next; };
struct GROUP { u8 unknown_0x0[0xC]; int criderAlive; RIDER *first; u8 unknown_0x14[8]; int hpRider; u8 unknown_0x20[4]; int pcrv; };
struct SWARM;
extern "C" void SwarmGroup_LayoutBands(SWARM *, GROUP *);
extern "C" float SMaxCrv(int);
extern "C" void Swarm_SetRiderState(SWARM *, RIDER *, int);
void SwarmGroup_PlaceRiders(SWARM *pswarm, GROUP *pgroup)
{
    int irider = 0;
    SwarmGroup_LayoutBands(pswarm, pgroup);
    float sCurve = SMaxCrv(pgroup->pcrv);
    for (RIDER *prider = pgroup->first; prider != 0; prider = prider->next) {
        prider->state = -1;
        Swarm_SetRiderState(pswarm, prider, 0);
        float count = (float)pgroup->criderAlive;
        prider->v = 0;
        prider->s = (sCurve * ((float)irider + 0.5f)) / count;
        prider->hp = pgroup->hpRider;
        irider++;
    }
}

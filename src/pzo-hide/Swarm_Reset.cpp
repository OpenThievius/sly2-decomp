// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" void func_0017F6B0(SWARM *);
extern "C" void ClearDle__FP3DLE(DLE *);
extern "C" void AppendDlEntry(DL *, void *);
extern "C" void ClearDl__FP2DL(DL *);
extern "C" void SwarmGroup_PlaceRiders(SWARM *, SWARMGROUP *);

extern "C" void Swarm_Reset(SWARM *swarm)
{
    func_0017F6B0(swarm);
    SWARMRIDER *rider = (SWARMRIDER *)swarm->dlDead.head;
    while (rider) {
        SWARMRIDER *next = (SWARMRIDER *)rider->dle.next;
        ClearDle__FP3DLE(&rider->dle);
        AppendDlEntry(&rider->group->dl, rider);
        rider = next;
    }
    ClearDl__FP2DL(&swarm->dlDead);
    for (int index = 0; index < swarm->cgroup; index++) {
        SWARMGROUP *group = &swarm->agroup[index];
        group->alive = group->total;
        SwarmGroup_PlaceRiders(swarm, group);
    }
}

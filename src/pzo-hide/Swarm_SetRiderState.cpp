// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" void RemoveDlEntry(DL *, void *);
extern "C" void AppendDlEntry(DL *, void *);
extern "C" void SwarmGroup_LayoutBands(SWARM *, SWARMGROUP *);
extern "C" void bevy_camera_follow_activity(void *, int, void *);
extern "C" char B_002DEB30[];

void Swarm_SetRiderState(SWARM *swarm, SWARMRIDER *rider, int state)
{
    if (state != rider->state) {
        rider->state = state;
        rider->tState = g_2dded0.t;
        if (state == 2) {
            SWARMGROUP *group = rider->group;
            int alive = group->alive - 1;
            group->alive = alive;
            RemoveDlEntry(&group->dl, rider);
            AppendDlEntry(&swarm->dlDead, rider);
            if (group->alive == 0)
                bevy_camera_follow_activity(B_002DEB30, 0x3A, swarm);
            SwarmGroup_LayoutBands(swarm, group);
        }
    }
}

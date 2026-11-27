// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "goalpost.h"
void AddGuardPost(STEPGUARDPOSTS *guard, int postA, int zoneA, int postB, int zoneB)
{
    int index = guard->cpost;
    guard->cpost = index + 1;
    POSTPAIR *post = &guard->apost[index];
    post->oidA = postA;
    post->oidVolumeA = zoneA;
    post->oidB = postB;
    post->oidVolumeB = zoneB;
}

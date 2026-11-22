// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "pathzone.h"

extern "C" void *PcgtPointInCgQuick(void *, QW);
extern "C" int CobstacleFindPathzoneBox(PATHZONE *, void *, QW, QW, int, OBSTACLE **);
extern "C" int FObstacleContainsPos(OBSTACLE *, QW);

int FPosFreeInPathzone(PATHZONE *zone, QW pos)
{
    OBSTACLE *obstacles[128];
    if (!PcgtPointInCgQuick(&zone->cg, pos))
        return 0;
    int count = CobstacleFindPathzoneBox(zone, 0, pos, pos, 0x80, obstacles);
    for (int index = 0; index < count; index++) {
        if (FObstacleContainsPos(obstacles[index], pos))
            return 0;
    }
    return 1;
}

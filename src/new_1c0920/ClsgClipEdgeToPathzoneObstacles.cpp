/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "pathzone.h"
/* a line segment of an edge clipped against a pathzone or an obstacle (ClsgClipEdgeToPathzone, ClsgClipEdgeToObstacle, ClsgMergeAlsg): 0x60 bytes, layout not recovered here */
struct LSG { u8 unknown_0x0[0x60]; };
extern "C" int ClsgClipEdgeToPathzone(PATHZONE *, QW, QW, int, LSG *, int);
extern "C" int CobstacleFindPathzoneBox(PATHZONE *, void *, QW, QW, int, OBSTACLE **);
extern "C" int ClsgClipEdgeToObstacle(OBSTACLE *, QW, QW, int, LSG *);
extern "C" int ClsgMergeAlsg(int, LSG *, int, LSG *, int, LSG *, int);
int ClsgClipEdgeToPathzoneObstacles(PATHZONE *ppathzone, QW pos1, QW pos2, int clsgMax, LSG *alsg)
{
    OBSTACLE *apobstacle[128];
    LSG alsgObstacle[2];
    int clsg = ClsgClipEdgeToPathzone(ppathzone, pos1, pos2, clsgMax, alsg, 2);
    if (clsg == 0)
        return 0;
    int cobstacle = CobstacleFindPathzoneBox(ppathzone, 0, pos1, pos2, 0x80, apobstacle);
    for (int iobstacle = 0; iobstacle < cobstacle; iobstacle++) {
        int clsgBlocked = ClsgClipEdgeToObstacle(apobstacle[iobstacle], pos1, pos2, 2, alsgObstacle);
        clsg = ClsgMergeAlsg(clsg, alsg, clsgBlocked, alsgObstacle, clsgMax, alsg, 1);
        if (clsg == 0)
            goto done;
    }
done:
    return clsg;
}

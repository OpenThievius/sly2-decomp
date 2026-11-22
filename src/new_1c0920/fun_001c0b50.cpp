// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "ps2inline.h"
#include "pathzone.h"
struct LSG { QW pos1; QW pos2; u8 unknown_0x20[0x40]; };
extern "C" {
void *PcgtPointInCgQuick(void *, QW, int);
QW PosClosestOnCgt(void *, QW);
int CobstacleFindPathzoneBox(PATHZONE *, void *, QW, QW, int, OBSTACLE **);
int FObstacleContainsPos(OBSTACLE *, QW);
QW ConvertAloPos(OBSTACLE *, int, QW);
int ClsgClipEdgeToPathzone(PATHZONE *, QW, QW, int, LSG *, int);
void ClosestPointOnSegment(QW, QW, QW, QW *, int, float *);
int FFindPathzoneClosestPoint(PATHZONE *, QW, QW *, int);
}
extern "C" float D_002A76DC;
int func_001C0B50(PATHZONE *ppathzone, QW pos, QW *pposOut)
{
    OBSTACLE *apobstacle[128];
    VECTOR posPrev;
    VECTOR posNext;
    VECTOR posBest;
    LSG alsg[1];
    VECTOR posSeg;
    float d;
    void *pcgt = PcgtPointInCgQuick(&ppathzone->cg, pos, 1);
    if (pcgt == 0)
        return 0;
    QW posClosest = PosClosestOnCgt(pcgt, pos);
    int cobstacle = CobstacleFindPathzoneBox(ppathzone, 0, posClosest, posClosest, 0x80, apobstacle);
    OBSTACLE *pobstacle = 0;
    for (int iobstacle = 0; iobstacle < cobstacle; iobstacle++) {
        if (FObstacleContainsPos(apobstacle[iobstacle], pos)) {
            pobstacle = apobstacle[iobstacle];
            break;
        }
    }
    if (pobstacle == 0) {
        *pposOut = posClosest;
        return 1;
    }
    posBest.z = 0.0f;
    posBest.y = 0.0f;
    posBest.x = 0.0f;
    float dBest = D_002A76DC;
    *(QW *)&posPrev = ConvertAloPos(pobstacle, 0, pobstacle->apos[0]);
    posPrev.z = FloatFromWord(LaneWordZ(posClosest));
    int ipos = 1;
    while (ipos < pobstacle->ccv) {
        *(QW *)&posNext = ConvertAloPos(pobstacle, 0, pobstacle->apos[ipos]);
        posNext.z = FloatFromWord(LaneWordZ(posClosest));
        int clsg = ClsgClipEdgeToPathzone(ppathzone, *(QW *)&posPrev, *(QW *)&posNext, 1, alsg, 2);
        for (int ilsg = 0; ilsg < clsg; ilsg++) {
            ClosestPointOnSegment(posClosest, (&alsg[ilsg])->pos1, alsg[ilsg].pos2, (QW *)&posSeg, 0, &d);
            if (d < dBest) {
                dBest = d;
                posBest = posSeg;
            }
        }
        posPrev = posNext;
        ipos++;
    }
    FFindPathzoneClosestPoint(ppathzone, *(QW *)&posBest, pposOut, 0);
    return 1;
}

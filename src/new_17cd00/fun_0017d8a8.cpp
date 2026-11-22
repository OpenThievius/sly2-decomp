/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "step.h"
#include "phys.h"
#include "sly2.h"
struct SWX { char pad[0x45CC]; void *graph; };
struct PZ { char pad[1]; };
struct PZLINK { char pad[0x128]; PZ *zoneFar; };
struct LINK { char pad[0x10]; PZ *zone; };
extern SWX B_003DD490;
extern "C" {
QW PosLoWorld(void *);
QW func_001C1EC0(void *, QW);
PZ *PpathzoneFindPos(QW, int);
int CpzlinkFindPath(void *, void *, QW, int, int, PZLINK **);
void FFindPathzoneClosestPoint(PZ *, QW, QW *, int);
}
void func_0017D8A8(GOALGOTO *goal)
{
    goal->cpzlink = 0;
    goal->targetResolved = goal->target;
    if (goal->fStraight)
        return;
    QW posGuard = PosLoWorld(goal->pstep);
    QW posTarget = func_001C1EC0(&goal->target, posGuard);
    PHYS *pphys = goal->pstep->pphys;
    LINK *plink = pphys ? pphys->plink : 0;
    PZ *zoneGuard = plink ? plink->zone : 0;
    PZ *zoneTarget = PpathzoneFindPos(posTarget, 0);
    int stay = 0;
    if (zoneTarget == 0) {
        stay = 1;
    } else if (zoneTarget != zoneGuard) {
        int count;
        if ((goal->cpzlink = CpzlinkFindPath(B_003DD490.graph, goal->pstep, posTarget, 1, 1, goal->apzlink)) <= 0) {
            if (goal->fLink == 0) {
                stay = 1;
            } else {
                count = CpzlinkFindPath(B_003DD490.graph, goal->pstep, posTarget, 0, 1, goal->apzlink);
                goal->cpzlink = count;
                if (count == 0) {
                    stay = 1;
                } else {
                    PZ *zoneNear;
                    if (goal->apzlink[0] == 0) {
                        goal->cpzlink = 0;
                        zoneNear = zoneGuard;
                    } else {
                        zoneNear = goal->apzlink[count - 1]->zoneFar;
                    }
                    goal->targetResolved.pcrv = 0;
                    goal->targetResolved.plo = 0;
                    FFindPathzoneClosestPoint(zoneNear, posTarget, &goal->targetResolved.pos, 1);
                }
            }
        }
    }
    if (stay) {
        goal->targetResolved.pos = posGuard;
        goal->targetResolved.plo = 0;
        goal->targetResolved.pcrv = 0;
    }
}

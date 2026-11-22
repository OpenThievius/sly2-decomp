/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goal.h"
#include "step.h"
#include "phys.h"
#include "sly2.h"
struct SWX { char pad[0x45CC]; void *graph; };
struct PZ { char pad[1]; };
struct PZLINK { char pad[0x128]; PZ *zoneFar; };
struct LINK { char pad[0x10]; PZ *zone; };
/* a GOAL subclass (GoalGoto family): the path state sits past GOAL's 0x30 bytes */
struct GOALGOTO : GOAL {
    char pad30[0x10];
    QW target0; QW target1;
    QW resolved0; QW resolved1;
    int pad80[(0xB4 - 0x80) / 4];
    int cpzlink; PZLINK *pzlink[1]; int fStraight; int fLink;
};
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
    goal->resolved0 = goal->target0;
    goal->resolved1 = goal->target1;
    if (goal->fStraight)
        return;
    QW posGuard = PosLoWorld(goal->pstep);
    QW posTarget = func_001C1EC0(&goal->target0, posGuard);
    PHYS *pphys = goal->pstep->pphys;
    LINK *plink = pphys ? pphys->plink : 0;
    PZ *zoneGuard = plink ? plink->zone : 0;
    PZ *zoneTarget = PpathzoneFindPos(posTarget, 0);
    int stay = 0;
    if (zoneTarget == 0) {
        stay = 1;
    } else if (zoneTarget != zoneGuard) {
        int count;
        if ((goal->cpzlink = CpzlinkFindPath(B_003DD490.graph, goal->pstep, posTarget, 1, 1, goal->pzlink)) <= 0) {
            if (goal->fLink == 0) {
                stay = 1;
            } else {
                count = CpzlinkFindPath(B_003DD490.graph, goal->pstep, posTarget, 0, 1, goal->pzlink);
                goal->cpzlink = count;
                if (count == 0) {
                    stay = 1;
                } else {
                    PZ *zoneNear;
                    if (goal->pzlink[0] == 0) {
                        goal->cpzlink = 0;
                        zoneNear = zoneGuard;
                    } else {
                        zoneNear = goal->pzlink[count - 1]->zoneFar;
                    }
                    *(int *)&goal->resolved0 = 0;
                    *((int *)&goal->resolved0 + 1) = 0;
                    FFindPathzoneClosestPoint(zoneNear, posTarget, &goal->resolved1, 1);
                }
            }
        }
    }
    if (stay) {
        goal->resolved1 = posGuard;
        *((int *)&goal->resolved0 + 1) = 0;
        *(int *)&goal->resolved0 = 0;
    }
}

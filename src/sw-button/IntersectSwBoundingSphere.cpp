// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "alloc.h"
#include "sw.h"
#include "oxa.h"
#include "geom.h"
#include "ps2inline.h"
#include "vu0inline.h"

extern "C" {
void *PvAllocStackImpl__Fi(ALLOCREQ *preq);
void UpdateSwAaox__FP2SW(SW *psw);
void func_00133E30(SW *psw);

void IntersectSwBoundingSphere(SW *psw, QW posCenter, int (*pfnFilter)(void *, GEOM *), void *pvContext, int *pcalo, float sRadius, GEOM ***papalo)
{
    int calo = 0;
    ALLOCREQ req;
    req.cb = 0x400;
    req.cbAlign = 0x10;
    GEOM **apgeom = (GEOM **)PvAllocStackImpl__Fi(&req);
    func_00133E30(psw);
    UpdateSwAaox__FP2SW(psw);
    for (OXA *poxa = (OXA *)psw->dlOxaWorld.head; poxa != 0; poxa = poxa->pnextWorld) {
        float sRadiusNode = poxa->sRadius;
        QW dpos = VectorSub(posCenter, poxa->posCenter);
        float sDistanceSquared = LaneX(SquaredLength(dpos));
        float sReach = sRadius + sRadiusNode;
        float sReachSquared = sReach * sReach;
        if (sReachSquared < sDistanceSquared) continue;
        for (GEOM *pgeom = (GEOM *)poxa->dlGeom.head; pgeom != 0; pgeom = pgeom->pgeomNext) {
            if ((pfnFilter == 0 || pfnFilter(pvContext, pgeom) != 0) && calo < 0x100) {
                apgeom[calo] = pgeom;
                calo++;
            }
        }
    }
    *papalo = apgeom;
    *pcalo = calo;
}
}

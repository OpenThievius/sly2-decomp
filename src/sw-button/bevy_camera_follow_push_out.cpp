// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "oxa.h"
#include "geom.h"
#include "sly2.h"
#include "alloc.h"
#include "vu0inline.h"
union BOXES { QW q[2]; float f[8]; };
extern "C" {
void *PvAllocStackImpl__Fi(ALLOCREQ *);
void UpdateSwAaox__FP2SW(SW *);
void func_00133E30(SW *);
void bevy_camera_follow_push_out(SW *psw, QW posA, QW posB, int (*pfn)(void *, void *), void *pvArg, int *pcount, GEOM ***plist)
{
    BOXES box;
    ALLOCREQ req;
    QW lo = VectorMiniXyz(posA, posB);
    QW hi = VectorMaxXyz(posA, posB);
    int count = 0;
    box.q[0] = lo;
    box.q[1] = hi;
    ALLOCREQ *preq = &req;
    int align = 0x10;
    req.cb = 0x400;
    preq->cbAlign = align;
    GEOM **list = (GEOM **)PvAllocStackImpl__Fi(preq);
    func_00133E30(psw);
    UpdateSwAaox__FP2SW(psw);
    for (OXA *poxa = (OXA *)psw->dlOxaWorld.head; poxa; poxa = poxa->pnextWorld) {
        if (poxa->aMin[0] > box.f[4] || poxa->aMax[0] < box.f[0] || poxa->aMin[1] > box.f[5] || poxa->aMax[1] < box.f[1] || poxa->aMin[2] > box.f[6] || poxa->aMax[2] < box.f[2])
            continue;
        GEOM *pgeom = (GEOM *)poxa->dlGeom.head;
        if (!pgeom) continue;
        GEOM **pslot = (GEOM **)(count * 4 + (sptr)list);
        do {
            if ((!pfn || pfn(pvArg, pgeom)) && count < 0x100) {
                *pslot++ = pgeom;
                count++;
            }
            pgeom = pgeom->pgeomNext;
        } while (pgeom);
    }
    *plist = list;
    *pcount = count;
}
}

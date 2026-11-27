// SPDX-License-Identifier: GPL-3.0-or-later
#include "vu0inline.h"
#include "ps2inline.h"
#include "types.h"
#include "sw.h"
#include "so.h"
#include "oxa.h"
#include "geom.h"
#include "xp.h"
union VU_SCALE { QW q; float g[4]; };
extern "C" {
void *PvAllocSlotheapImpl(SLOTHEAP *);
QW ConvertXfPos(int, XF *, QW);
void RecalcSwXpMovement(SW *, int, XP **);
extern float D_FLT_002BFD30;
extern float D_FLT_002BFD34;
void PxpAdd(SW *psw, GEOM *pgeomA, GEOM *pgeomB, QW pos, QW vel, int arg5, int arg6, int arg7, float gScale, XP **ppxpHead)
{
    VU_SCALE scale;
    XP *pxp;
    XPD *pxpd;
    XP *pxpNew = (XP *)PvAllocSlotheapImpl(&psw->slotheapMq);
    pxp = pxpNew;
    pxpNew->axpd[0].pos = pos;
    scale.q = VectorFromFloat(-gScale);
    pxpNew->axpd[1].pos = ScaleAddX(pos, vel, scale.q);
    pxpNew->normal = vel;
    int ixpd = 0;
    do {
        pxpd = &pxp->axpd[ixpd];
        if (ixpd == 0)
            pxpd->pgeom = pgeomA;
        else
            pxpd->pgeom = pgeomB;
        GEOM *pgeom = pxpd->pgeom;
        if (pgeom) {
            pxpd->pxf = pgeom->pxf;
            SO *pso = pgeom->pso;
            pxpd->pso = pso;
            pxpd->psoRoot = pso->poxa->owner;
        }
        ixpd++;
        pxpd->posConv = ConvertXfPos(0, pxpd->pxf, pxpd->pos);
    } while (ixpd < 2);
    pxp->gScale = gScale;
    pxp->kind = arg5;
    pxp->friction = D_FLT_002BFD30;
    pxp->bounce = D_FLT_002BFD34;
    pxp->nUser = arg6;
    pxp->field_0xA4 = arg7;
    ixpd = 0;
    do {
        pxpd = &pxp->axpd[ixpd];
        SO *pso = pxpd->pso;
        if (pso)
            pso->Slot55(pxp, ixpd);
        ixpd++;
    } while (ixpd < 2);
    RecalcSwXpMovement(psw, 1, &pxp);
    XP *pxpLast = pxp;
    while (pxpLast->pxpNext)
        pxpLast = pxpLast->pxpNext;
    pxpLast->pxpNext = *ppxpHead;
    *ppxpHead = pxp;
}
}

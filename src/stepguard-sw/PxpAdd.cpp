// SPDX-License-Identifier: GPL-3.0-or-later
#include "vu0inline.h"
#include "ps2inline.h"
#include "types.h"
#include "sw.h"
#include "so.h"
#include "oxa.h"
struct XPOBJ { int unk0; SO *powner; };
struct XPD { XPOBJ *pobj; int unk4; SO *psoOxaOwner; SO *pso; QW pos; QW posConv; QW vel; };
struct XP {
    XPD xpd[2];
    QW velBase;
    float gA; float gB; float gC; int n9C; int nA0; int nA4; int unkA8; XP *pxpNext;
};
union VU_SCALE { QW q; float g[4]; };
extern "C" {
void *PvAllocSlotheapImpl(SLOTHEAP *);
QW ConvertXfPos(int, int, QW);
void RecalcSwXpMovement(SW *, int, XP **);
extern float D_FLT_002BFD30;
extern float D_FLT_002BFD34;
void PxpAdd(SW *psw, void *pobjA, void *pobjB, QW pos, QW vel, int arg5, int arg6, int arg7, float gScale, XP **ppxpHead)
{
    VU_SCALE scale;
    XP *pxp;
    XPD *pxpd;
    XP *pxpNew = (XP *)PvAllocSlotheapImpl(&psw->slotheapMq);
    pxp = pxpNew;
    pxpNew->xpd[0].pos = pos;
    scale.q = VectorFromFloat(-gScale);
    pxpNew->xpd[1].pos = ScaleAddX(pos, vel, scale.q);
    pxpNew->velBase = vel;
    int ixpd = 0;
    do {
        pxpd = &pxp->xpd[ixpd];
        if (ixpd == 0)
            pxpd->pobj = (XPOBJ *)pobjA;
        else
            pxpd->pobj = (XPOBJ *)pobjB;
        XPOBJ *pobj = pxpd->pobj;
        if (pobj) {
            pxpd->unk4 = pobj->unk0;
            SO *powner = pobj->powner;
            pxpd->pso = powner;
            pxpd->psoOxaOwner = powner->poxa->owner;
        }
        ixpd++;
        pxpd->posConv = ConvertXfPos(0, pxpd->unk4, pxpd->pos);
    } while (ixpd < 2);
    pxp->gA = gScale;
    pxp->n9C = arg5;
    pxp->gB = D_FLT_002BFD30;
    pxp->gC = D_FLT_002BFD34;
    pxp->nA0 = arg6;
    pxp->nA4 = arg7;
    ixpd = 0;
    do {
        pxpd = &pxp->xpd[ixpd];
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

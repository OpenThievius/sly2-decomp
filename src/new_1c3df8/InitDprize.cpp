// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"
#include "sw.h"
extern float D_002A7710;
extern "C" void InitSo(DPRIZE *);
extern "C" void SetAloInteract(DPRIZE *, int, int);
extern "C" void InitDprize(DPRIZE *dprize)
{
    InitSo(dprize);
    SetAloInteract(dprize, 0x17E, 8);
    dprize->collectable = 1;
    dprize->field_0x21C = 30.0f;
    dprize->dprizes = -1;
    dprize->dprizesInitial = 0;
    dprize->smaGoal = -1;
    dprize->aoidploGlint[0].oid = -1;
    dprize->aoidploGlint[1].oid = -1;
    dprize->aoidploGlint[2].oid = -1;
    dprize->aoidploB[0].oid = -1;
    dprize->aoidploB[1].oid = -1;
    dprize->aoidploB[2].oid = -1;
    dprize->tExpire = D_002A7710;
    dprize->field_0x224 = -1;
    int heap = (dprize->grfSw & 1) == 0;
    if (heap)
        dprize->pgrfentry->grf |= 2;
    else
        dprize->grfSw |= 2;
}

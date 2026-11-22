// SPDX-License-Identifier: GPL-3.0-or-later
#include "slotso.h"
#include "sly2.h"
extern "C" void InitSo(SLOTSO *);
extern int D_002C0230[6];
extern "C" void func_001B0B78(SLOTSO *pso)
{
    InitSo(pso);
    pso->field_0x150 = 400.0f;
    pso->field_0x154 = 800.0f;
    pso->field_0x158 = 2.0f;
    pso->field_0x15C = 6.0f;
    pso->field_0x160 = 6.0f;
    pso->field_0x164 = 10.0f;
    pso->dtFade = 1.0f;
    SLOTDEF *pslot = pso->aslot;
    for (int islot = 0; islot < 6; islot++) {
        pslot->oid = -1;
        pslot->def = D_002C0230[islot];
        pslot++;
    }
    pso->field_0x1CC = 300.0f;
    pso->field_0x1D0 = 1000.0f;
    pso->state = -1;
    pso->field_0x230 = -1;
    unsigned grf = pso->grfSw;
    if (((grf ^ 1) & 1) != 0)
        *(unsigned *)grf |= 2;
    else
        pso->grfSw = grf | 2;
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "sohit.h"
#include "sw.h"
extern "C" {
void InitSo(SOHIT *pso);
extern QW D_002BE7D0;
extern SOHITBYTES8 D_002BE7E0;

void func_0017F090(SOHIT *pso) {
    InitSo(pso);
    pso->hpMax = 0xA;
    pso->vecKnock = D_002BE7D0;
    pso->field_0x1B0 = D_002BE7E0;
    if (!(pso->grfSw & 1)) {
        pso->pgrfentry->grf |= 2;
    } else {
        pso->grfSw |= 2;
    }
}
}

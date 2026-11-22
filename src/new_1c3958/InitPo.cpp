// SPDX-License-Identifier: GPL-3.0-or-later
#include "po.h"
#include "sw.h"

extern "C" {
void InitSo(SO *pso);

void InitPo(PO *ppo) {
    InitSo(ppo);
    ppo->magnet.field_0x0 = 1;
    ppo->ppoSelf = ppo;
    if (!(ppo->grfSw & 1)) {
        ppo->pgrfentry->grf |= 2;
    } else {
        ppo->grfSw |= 2;
    }
}
}

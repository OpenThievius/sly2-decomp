// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
#include "oxa.h"

extern "C" {
void RemoveDlEntry(DL *pdl, void *pv);
extern DL B_003E11B8;

void func_001F4BA8(SO *pso) {
    OXA *poxa = pso->poxa;
    if (poxa == 0)
        return;
    u64 grf = poxa->grf;
    if ((grf & 1) == 0)
        return;
    poxa->grf = grf & ~1UL;
    RemoveDlEntry(&B_003E11B8, pso->poxa);
}
}

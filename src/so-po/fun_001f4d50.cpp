// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
#include "oxa.h"

extern "C" {
void RemoveDlEntry(DL *pdl, void *pv);
void func_001F4BA8(SO *pso);
extern DL B_003E11C4;

void func_001F4D50(SO *pso) {
    func_001F4BA8(pso);
    OXA *poxa = pso->poxa;
    if (poxa != 0) {
        u64 grf = poxa->grf;
        if (grf & 2) {
            poxa->grf = grf & ~2UL;
            RemoveDlEntry(&B_003E11C4, pso->poxa);
        }
    }
}
}

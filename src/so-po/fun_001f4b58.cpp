// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
#include "oxa.h"

extern "C" {
void AppendDlEntry(DL *pdl, void *pv);
extern DL B_003E11B8;

void func_001F4B58(SO *pso) {
    OXA *poxa = pso->poxa;
    if (poxa != 0) {
        u64 grf = poxa->grf;
        if ((grf & 1) == 0) {
            poxa->grf = grf | 1;
            AppendDlEntry(&B_003E11B8, pso->poxa);
        }
    }
}
}

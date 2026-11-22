// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
extern "C" {
extern char B_003DD490[];
SO *func_001A5BF0(SO *);
void UpdateSwPox(void *, void *, void *, int);
void func_001F4BF8(void *);
}
void func_00204F78(SO *pso, SO *plo, int fAdd)
{
    SO *anc = func_001A5BF0(plo);
    while (anc && !anc->poxa)
        anc = anc->psoParent;
    OXA *pox = pso->poxa;
    if (pox != 0 && anc != 0 && anc->poxa != 0)
        UpdateSwPox(B_003DD490, pox, anc->poxa, fAdd ? 1 : 2);
    func_001F4BF8(pso);
}

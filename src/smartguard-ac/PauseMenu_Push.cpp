// SPDX-License-Identifier: GPL-3.0-or-later
#include "pausemenu.h"
extern "C" void *memset(void *, int, unsigned int);
extern "C" void PauseMenu_SetState(PAUSEMENU *, int);
extern "C" int func_001B0108(PAUSEMENU *);
extern "C" void PauseMenu_Push(PAUSEMENU *pmenu, int citem, PAUSEITEM *aitem, PAUSEBLOT *pblot, PAUSELABELS *plabels)
{
    if (pblot == 0 && pmenu->depth > 0)
        pblot = pmenu->apage[pmenu->depth - 1].pblot;
    PAUSEPAGE *ppage = &pmenu->apage[pmenu->depth++];
    memset(ppage, 0, 0x1C);
    ppage->aitem = aitem;
    ppage->citem = citem;
    ppage->pblot = pblot;
    ppage->plabels = plabels;
    ppage->fSub = 0;
    PauseMenu_SetState(pmenu, 1);
    for (int iitem = 0; iitem < ppage->citem; iitem++) {
        PAUSEITEM *pitem = &ppage->aitem[iitem];
        if (pitem->pfnEnter) pitem->pfnEnter(pitem);
    }
    if (func_001B0108(pmenu)) {
        int depth = pmenu->depth;
        pmenu->depthNext = depth;
        pmenu->depth = depth - 1;
    }
}

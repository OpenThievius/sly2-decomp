// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "pausemenu.h"
extern "C" void PauseMenu_SetState(PAUSEMENU *, int);
extern "C" void func_001AF390(PAUSEMENU *pmenu, int citem, PAUSEITEM *aitem)
{
    PauseMenu_SetState(pmenu, 3);
    PAUSELABELS *plabels;
    PAUSEBLOT *pblot;
    PAUSEPAGE *ppageNew;
    int depth = pmenu->depth;
    if (depth > 0) {
        ppageNew = &pmenu->apage[depth - 1];
        pblot = ppageNew->pblot;
        plabels = ppageNew->plabels;
    }
    pmenu->depthNext = depth + 1;
    ppageNew = &pmenu->apage[depth];
    memset(ppageNew, 0, 0x1C);
    ppageNew->aitem = aitem;
    ppageNew->pblot = pblot;
    ppageNew->fSub = 1;
    ppageNew->plabels = plabels;
    ppageNew->citem = citem;
    for (int iitem = 0; iitem < ppageNew->citem; iitem++) {
        PAUSEITEM *pitem = &ppageNew->aitem[iitem];
        if (pitem->pfnEnter)
            pitem->pfnEnter(pitem);
    }
}

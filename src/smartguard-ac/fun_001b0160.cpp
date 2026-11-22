// SPDX-License-Identifier: GPL-3.0-or-later
#include "pausemenu.h"
extern PAUSEITEM D_002BFDA8[];
int CGc_FFindScreen();
int func_001B0160(PAUSEMENU *pmenu)
{
    if (!CGc_FFindScreen()) return 0;
    int depth = pmenu->depth;
    if (depth <= 0) return 0;
    PAUSEPAGE *ppage = &pmenu->apage[depth - 1];
    if (pmenu->state == 1) {
        int depthNext = pmenu->depthNext;
        if (depth < depthNext) ppage = &pmenu->apage[depthNext - 1];
    }
    return ppage->aitem == D_002BFDA8;
}

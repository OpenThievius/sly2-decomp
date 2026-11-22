/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pausemenu.h"

void func_001AF390(PAUSEMENU *pmenu, s32 citem, PAUSEITEM *aitem);
extern PAUSEMENU B_003D9ED0;

/* an item's pfnActivate: opens a sub-page from the item's citemSub and aitemSub */
void func_001B06D8(PAUSEITEM *pitem) {
    func_001AF390(&B_003D9ED0, pitem->citemSub, pitem->aitemSub);
    if (pitem != 0) {
        pitem->grf = pitem->grf | 2;
    }
}

/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "gcnode.h"
extern "C" {
void func_00255F38(void *, unsigned *);
extern unsigned B_002DD2D0;
extern s32 g_2dd598;

GNODE *func_002560C8(GNODE *pnode) {
    pnode->cref = 0;
    func_00255F38(pnode, &B_002DD2D0);
    pnode->gen = g_2dd598;
    return pnode;
}
}

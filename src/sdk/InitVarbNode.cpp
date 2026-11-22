/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "gcnode.h"
extern "C" {
void LinkVarbNode(void *, unsigned *);
extern unsigned B_002DD290;
extern s32 g_2dd598;

GNODE *InitVarbNode(GNODE *pnode) {
    pnode->cref = 0;
    LinkVarbNode(pnode, &B_002DD290);
    pnode->gen = g_2dd598;
    return pnode;
}
}

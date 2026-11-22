/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "gcnode.h"
extern "C" {
void LinkProcNode(void *, unsigned *);
extern unsigned B_002DD2B0;
extern s32 g_2dd598;

GNODE *InitProcNode(GNODE *pnode) {
    pnode->cref = 0;
    LinkProcNode(pnode, &B_002DD2B0);
    pnode->gen = g_2dd598;
    return pnode;
}
}

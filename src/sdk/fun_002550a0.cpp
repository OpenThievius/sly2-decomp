/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "gcnode.h"
extern "C" {
void LinkPairNode(GNODE *, GNODE **);
extern GNODE *B_002DD280;
extern s32 g_2dd598;

GNODE *func_002550A0(GNODE *pnode) {
    pnode->cref = 0;
    LinkPairNode(pnode, &B_002DD280);
    pnode->gen = g_2dd598;
    return pnode;
}
}

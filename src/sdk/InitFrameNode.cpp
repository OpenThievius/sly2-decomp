/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "gcnode.h"
extern "C" {
void LinkFrameNode(void *, unsigned *);
extern unsigned B_002DD2A0;
extern s32 g_2dd598;

GNODE *InitFrameNode(GNODE *pnode) {
    pnode->cref = 0;
    LinkFrameNode(pnode, &B_002DD2A0);
    pnode->gen = g_2dd598;
    return pnode;
}
}

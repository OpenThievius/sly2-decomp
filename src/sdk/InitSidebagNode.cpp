/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "gcnode.h"
extern "C" {
void LinkSidebagNode(void *, unsigned *);
extern unsigned B_002DD2C0;
extern s32 g_2dd598;

GNODE *InitSidebagNode(GNODE *pnode) {
    pnode->cref = 0;
    LinkSidebagNode(pnode, &B_002DD2C0);
    pnode->gen = g_2dd598;
    return pnode;
}
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "gcnode.h"
extern "C" {
void LinkSidebagNode(GNODE *, unsigned *);
void UnlinkSidebagNode(GNODE *);
extern unsigned B_002DD2CC;

void func_00258178(GNODE *pnode) {
    UnlinkSidebagNode(pnode);
    LinkSidebagNode(pnode, &B_002DD2CC);
    pnode->unused = 1;
}

}

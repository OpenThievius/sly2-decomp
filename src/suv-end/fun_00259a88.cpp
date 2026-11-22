// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
/* A pool node of the frame lists (UnlinkFrameNode, LinkFrameNode): word 1 holds its prev/next links, bit 15 is a spare bit. */
struct FRAMENODE {
    s32 unknown_0x0;
    u32 links;
};
extern "C" {
void LinkFrameNode(FRAMENODE *, unsigned *);
void UnlinkFrameNode(FRAMENODE *);
extern unsigned B_002DD2AC;

void func_00259A88(FRAMENODE *pnode) {
    UnlinkFrameNode(pnode);
    LinkFrameNode(pnode, &B_002DD2AC);
    pnode->links |= 0x8000;
}
}

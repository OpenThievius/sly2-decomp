// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
struct LinksSidebag257AB0 {
    unsigned prevIndex : 13;
    unsigned prevPool : 2;
    unsigned unused15 : 1;
    unsigned nextIndex : 13;
    unsigned nextPool : 2;
    unsigned mark : 1;
};
struct SidebagNode257AB0 {
    u8 unknown_0x0[4];
    LinksSidebag257AB0 links;
    u8 unknown_0x8[4];
};
struct SlotHeap257AB0;
extern "C" {
extern SidebagNode257AB0 *B_002DD2C0;
extern SidebagNode257AB0 *B_002DD2C8;
extern SidebagNode257AB0 *B_00452138[];
extern SlotHeap257AB0 B_00452148;
extern unsigned g_2dd598[];
void UnlinkSidebagNode(SidebagNode257AB0 *);
void FreeSlotheapPv(SlotHeap257AB0 *, void *);
}

static inline SidebagNode257AB0 *SidebagNodeFromLink(unsigned index, unsigned pool) {
    if (index == 0 && pool == 0)
        return 0;
    return B_00452138[pool] + index;
}

extern "C" void SweepSidebags(void) {
    SidebagNode257AB0 *current;
    for (current = B_002DD2C0; current != B_002DD2C8;) {
        if (current->links.mark != g_2dd598[0])
            current->links.mark = g_2dd598[0];
        SidebagNode257AB0 *next;
        next = SidebagNodeFromLink(current->links.nextIndex, current->links.nextPool);
        current = next;
    }
    while (current != 0) {
        SidebagNode257AB0 *node = current;
        SidebagNode257AB0 *next;
        next = SidebagNodeFromLink(node->links.nextIndex, node->links.nextPool);
        current = next;
        if (node->links.mark != g_2dd598[0]) {
            UnlinkSidebagNode(node);
            FreeSlotheapPv(&B_00452148, node);
        }
    }
}

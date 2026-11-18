// SPDX-License-Identifier: GPL-3.0-or-later
struct LinksVarb257678 {
    unsigned prevIndex : 13;
    unsigned prevPool : 2;
    unsigned unused15 : 1;
    unsigned nextIndex : 13;
    unsigned nextPool : 2;
    unsigned mark : 1;
};
struct VarbNode257678 {
    int pad0;
    LinksVarb257678 links;
    char pad8[0x10];
};
struct SlotHeap257678;
extern "C" {
extern VarbNode257678 *B_002DD290;
extern VarbNode257678 *B_002DD298;
extern VarbNode257678 *B_004520C0[];
extern SlotHeap257678 B_004520D0;
extern unsigned g_2dd598[];
void UnlinkVarbNode(VarbNode257678 *);
void FreeSlotheapPv(SlotHeap257678 *, void *);
}

static inline VarbNode257678 *VarbNodeFromLink(unsigned index, unsigned pool) {
    if (index == 0 && pool == 0)
        return 0;
    return B_004520C0[pool] + index;
}

extern "C" void SweepVarbs(void) {
    VarbNode257678 *current;
    for (current = B_002DD290; current != B_002DD298;) {
        if (current->links.mark != g_2dd598[0])
            current->links.mark = g_2dd598[0];
        VarbNode257678 *next;
        next = VarbNodeFromLink(current->links.nextIndex, current->links.nextPool);
        current = next;
    }
    while (current != 0) {
        VarbNode257678 *node = current;
        VarbNode257678 *next;
        next = VarbNodeFromLink(node->links.nextIndex, node->links.nextPool);
        current = next;
        if (node->links.mark != g_2dd598[0]) {
            UnlinkVarbNode(node);
            FreeSlotheapPv(&B_004520D0, node);
        }
    }
}

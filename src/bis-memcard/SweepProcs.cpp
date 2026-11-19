// SPDX-License-Identifier: GPL-3.0-or-later
struct LinksProc257948 {
    unsigned prevIndex : 13;
    unsigned prevPool : 2;
    unsigned unused15 : 1;
    unsigned nextIndex : 13;
    unsigned nextPool : 2;
    unsigned mark : 1;
};
struct ProcNode257948 {
    int pad0;
    LinksProc257948 links;
    char pad8[0x14];
};
struct SlotHeap257948;
extern "C" {
extern ProcNode257948 *B_002DD2B0;
extern ProcNode257948 *B_002DD2B8;
extern ProcNode257948 *B_00452110[];
extern SlotHeap257948 B_00452120;
extern unsigned g_2dd598[];
void UnlinkProcNode(ProcNode257948 *);
void FreeSlotheapPv(SlotHeap257948 *, void *);
}

static inline ProcNode257948 *ProcNodeFromLink(unsigned index, unsigned pool) {
    if (index == 0 && pool == 0)
        return 0;
    return B_00452110[pool] + index;
}

extern "C" void SweepProcs(void) {
    ProcNode257948 *current;
    for (current = B_002DD2B0; current != B_002DD2B8;) {
        if (current->links.mark != g_2dd598[0])
            current->links.mark = g_2dd598[0];
        ProcNode257948 *next;
        next = ProcNodeFromLink(current->links.nextIndex, current->links.nextPool);
        current = next;
    }
    while (current != 0) {
        ProcNode257948 *node = current;
        ProcNode257948 *next;
        next = ProcNodeFromLink(node->links.nextIndex, node->links.nextPool);
        current = next;
        if (node->links.mark != g_2dd598[0]) {
            UnlinkProcNode(node);
            FreeSlotheapPv(&B_00452120, node);
        }
    }
}

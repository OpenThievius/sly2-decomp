// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
struct LinksProc257C18 {
    unsigned prevIndex : 13;
    unsigned prevPool : 2;
    unsigned unused15 : 1;
    unsigned nextIndex : 13;
    unsigned nextPool : 2;
    unsigned mark : 1;
};
struct ProcNode257C18 {
    u8 unknown_0x0[4];
    LinksProc257C18 links;
    u8 unknown_0x8[0xC];
};
struct SlotHeap257C18;
extern "C" {
extern ProcNode257C18 *B_002DD2D0;
extern ProcNode257C18 *B_002DD2D8;
extern ProcNode257C18 *B_00452160[];
extern SlotHeap257C18 B_00452170;
extern unsigned g_2dd598[];
void func_00256120(ProcNode257C18 *);
void FreeSlotheapPv(SlotHeap257C18 *, void *);
}

static inline ProcNode257C18 *ProcNodeFromLink(unsigned index, unsigned pool) {
    if (index == 0 && pool == 0)
        return 0;
    return B_00452160[pool] + index;
}

extern "C" void func_00257C18(void) {
    ProcNode257C18 *current;
    for (current = B_002DD2D0; current != B_002DD2D8;) {
        if (current->links.mark != g_2dd598[0])
            current->links.mark = g_2dd598[0];
        ProcNode257C18 *next;
        next = ProcNodeFromLink(current->links.nextIndex, current->links.nextPool);
        current = next;
    }
    while (current != 0) {
        ProcNode257C18 *node = current;
        ProcNode257C18 *next;
        next = ProcNodeFromLink(node->links.nextIndex, node->links.nextPool);
        current = next;
        if (node->links.mark != g_2dd598[0]) {
            func_00256120(node);
            FreeSlotheapPv(&B_00452170, node);
        }
    }
}

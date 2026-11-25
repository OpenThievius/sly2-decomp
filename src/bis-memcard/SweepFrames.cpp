// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
struct Links257510 {
    unsigned prevIndex : 13;
    unsigned prevPool : 2;
    unsigned unused15 : 1;
    unsigned nextIndex : 13;
    unsigned nextPool : 2;
    unsigned mark : 1;
};
struct FrameNode257510 {
    u8 unknown_0x0[4];
    Links257510 links;
    u8 unknown_0x8[0x20];
};
struct SlotHeap257510;
extern "C" {
extern FrameNode257510 *B_002DD2A0;
extern FrameNode257510 *B_002DD2A8;
extern FrameNode257510 *B_004520E8[];
extern SlotHeap257510 B_004520F8;
extern unsigned g_2dd598[];
void UnlinkFrameNode(FrameNode257510 *);
void FreeSlotheapPv(SlotHeap257510 *, void *);
}

static inline FrameNode257510 *FrameNodeFromLink(unsigned index, unsigned pool) {
    if (index == 0 && pool == 0)
        return 0;
    return B_004520E8[pool] + index;
}

extern "C" void SweepFrames(void) {
    FrameNode257510 *current;
    for (current = B_002DD2A0; current != B_002DD2A8;) {
        if (current->links.mark != g_2dd598[0])
            current->links.mark = g_2dd598[0];
        FrameNode257510 *next;
        next = FrameNodeFromLink(current->links.nextIndex, current->links.nextPool);
        current = next;
    }
    while (current != 0) {
        FrameNode257510 *node = current;
        FrameNode257510 *next;
        next = FrameNodeFromLink(node->links.nextIndex, node->links.nextPool);
        current = next;
        if (node->links.mark != g_2dd598[0]) {
            UnlinkFrameNode(node);
            FreeSlotheapPv(&B_004520F8, node);
        }
    }
}

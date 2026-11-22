// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
/* the object func_001BEAD0 adds children to and the children's vtable: classes unknown, slot 9 (0x48) is called on a new child */
struct ROGCHILDVT { u8 unknown_0x0[0x48]; short delta; short index; void (*fn)(void *); };
struct ROGCHILD { u8 unknown_0x0[0xC]; ROGCHILDVT *vt; u8 unknown_0x10[0x14C]; int flagA; int flagB; };
struct ROGPARENT { u8 unknown_0x0[0x104]; int count; ROGCHILD *items[1]; };
extern "C" {
void func_001BEAD0(ROGPARENT *parent, ROGCHILD *child) {
    if (child) {
        int count = parent->count;
        parent->items[count] = child;
        parent->count = count + 1;
        child->flagB = 1;
        child->flagA = 1;
        child->vt->fn((char *)child + child->vt->delta);
    }
}
}

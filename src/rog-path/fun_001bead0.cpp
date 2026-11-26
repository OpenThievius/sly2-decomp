// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
/* the object func_001BEAD0 adds children to: class unknown; each child is an LO (its slot 9, Remove, is called on a new child) */
struct ROGCHILD : LO { u8 unknown_0x50[0x10C]; int flagA; int flagB; };
struct ROGPARENT { u8 unknown_0x0[0x104]; int count; ROGCHILD *items[1]; };
extern "C" {
void func_001BEAD0(ROGPARENT *parent, ROGCHILD *child) {
    if (child) {
        int count = parent->count;
        parent->items[count] = child;
        parent->count = count + 1;
        child->flagB = 1;
        child->flagA = 1;
        child->Remove();
    }
}
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct SLOTHEAP;
extern struct SLOTHEAP B_003E1AD8;
void *PvAllocSlotheapImpl(struct SLOTHEAP *pslotheap);

/* the callers pass the block size (0x40, 0xD0); the slot heap ignores it, as a class operator new does */
void *func_0020C010(u32 cb) {
    return PvAllocSlotheapImpl(&B_003E1AD8);
}

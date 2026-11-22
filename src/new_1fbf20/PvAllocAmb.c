// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct SLOTHEAP;
void *PvAllocSlotheapImpl(struct SLOTHEAP *pslotheap);
extern struct SLOTHEAP B_003DD05C; /* the emitters' slot heap (AMB, 0x70-byte slots; the sound system's heapAmb) */

void *PvAllocAmb(u32 cb) { /* the class's operator new: cb (the object size) is not used */
    return PvAllocSlotheapImpl(&B_003DD05C);
}

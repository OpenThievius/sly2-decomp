// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct SLOTHEAP;
void *PvAllocSlotheapImpl(struct SLOTHEAP *pslotheap);
extern struct SLOTHEAP B_003DD074; /* the stream emitters' slot heap (0x3C0-byte slots; the sound system's heapStreamAmb) */

void *PvAllocStreamAmb(u32 cb) { /* the class's operator new: cb (the object size) is not used */
    return PvAllocSlotheapImpl(&B_003DD074);
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct SLOTHEAP;
void FreeSlotheapPv(struct SLOTHEAP *pslotheap, void *pv);
extern struct SLOTHEAP B_003DD05C; /* the emitters' slot heap (AMB, 0x70-byte slots; the sound system's heapAmb) */

void FreeAmb(void *pv) {
    FreeSlotheapPv(&B_003DD05C, pv);
}

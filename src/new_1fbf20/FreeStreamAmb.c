// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct SLOTHEAP;
void FreeSlotheapPv(struct SLOTHEAP *pslotheap, void *pv);
extern struct SLOTHEAP B_003DD074; /* the stream emitters' slot heap (0x3C0-byte slots; the sound system's heapStreamAmb) */

void FreeStreamAmb(void *pv) {
    FreeSlotheapPv(&B_003DD074, pv);
}

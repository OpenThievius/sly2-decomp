// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct SLOTHEAP;
extern struct SLOTHEAP B_003E1AD8;
void FreeSlotheapPv(struct SLOTHEAP *pslotheap, void *pv);

void func_0020C030(void *pv) {
    FreeSlotheapPv(&B_003E1AD8, pv);
}

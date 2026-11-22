// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct SLOTHEAP;
extern struct SLOTHEAP B_003E1AF0;
void FreeSlotheapPv(struct SLOTHEAP *pslotheap, void *pv);

void func_0020CA20(void *pv) {
    FreeSlotheapPv(&B_003E1AF0, pv);
}

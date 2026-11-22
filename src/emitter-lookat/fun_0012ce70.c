/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct SLOTHEAP;
extern struct SLOTHEAP B_003E1254;
void FreeSlotheapPv(struct SLOTHEAP *pslotheap, void **ppv);

void func_0012CE70(void **ppv) {
    FreeSlotheapPv(&B_003E1254, ppv);
}

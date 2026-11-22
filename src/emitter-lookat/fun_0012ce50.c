/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct SLOTHEAP;
extern struct SLOTHEAP B_003E1254;
char *PvAllocSlotheapImpl(struct SLOTHEAP *pslotheap);

void func_0012CE50(void) {
    PvAllocSlotheapImpl(&B_003E1254);
}

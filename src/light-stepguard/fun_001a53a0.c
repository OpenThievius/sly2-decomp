/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "crefboxes.h"

/* The part of an LO this reads: its root link (lo.h's `proot`, C++ only), a slot that holds the root object. */
struct LOROOTVIEW {
    u8 unknown_0x0[0x14];
    /* 0x14 */ struct LOROOTVIEW **proot;
};

extern struct SLOTHEAP B_003E0E1C;

void func_001A53A0(struct LOROOTVIEW *plo) {
    struct LOROOTVIEW **pproot;

    if (plo->proot == 0) {
        pproot = (struct LOROOTVIEW **)PvAllocSlotheapImpl(&B_003E0E1C);
        plo->proot = pproot;
        *pproot = plo;
    }
}

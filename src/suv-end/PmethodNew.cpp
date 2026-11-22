// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
extern "C" {
void *PvAllocSlotheapImpl(SLOTHEAP *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void CGc_Collect(void *);
void func_002560C8(void *);
extern SLOTHEAP B_00452170;
extern void *B_00452160[];
extern unsigned g_2dd2d4;
extern int B_003E0EA4;
extern char g_2dd598;
void *PmethodNew(void)
{
    if (!B_00452170.pslotFree) {
        if (!B_003E0EA4 || g_2dd2d4 >= 4) CGc_Collect(&g_2dd598);
        if (!B_00452170.pslotFree) {
            void *chunk = PvAllocSlotheapImpl(&B_00452170);
            if (g_2dd2d4) FreeSlotheapPv(&B_00452170, chunk);
            B_00452160[g_2dd2d4++] = chunk;
        }
    }
    char *p = (char *)PvAllocSlotheapImpl(&B_00452170);
    func_002560C8(p);

    return p;
}
}

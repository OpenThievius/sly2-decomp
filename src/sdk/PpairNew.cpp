// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
#include "pairnode.h"
extern "C" {
void *PvAllocSlotheapImpl(SLOTHEAP *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void CGc_Collect(void *);
void func_002550A0(void *);
extern SLOTHEAP B_004520A8;
extern void *B_00452098[];
extern unsigned B_002DD284;
extern int B_003E0EA4;
extern char g_2dd598;
void *PpairNew(void)
{
    if (!B_004520A8.pslotFree) {
        if (!B_003E0EA4 || B_002DD284 >= 4) CGc_Collect(&g_2dd598);
        if (!B_004520A8.pslotFree) {
            void *chunk = PvAllocSlotheapImpl(&B_004520A8);
            if (B_002DD284) FreeSlotheapPv(&B_004520A8, chunk);
            B_00452098[B_002DD284++] = chunk;
        }
    }
    PAIRNODE *p = (PAIRNODE *)PvAllocSlotheapImpl(&B_004520A8);
    func_002550A0(p);
    p->field_0x8 = -1;
    p->field_0x10 = 0;
    return p;
}
}

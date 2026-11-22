// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
#include "sidebag.h"
extern "C" {
void *PvAllocSlotheapImpl(SLOTHEAP *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void CGc_Collect(void *);
void InitSidebagNode(void *);
extern SLOTHEAP B_00452148;
extern void *B_00452138[];
extern unsigned B_002DD2C4;
extern int B_003E0EA4;
extern char g_2dd598;
void *PsidebagNew(void)
{
    if (!B_00452148.pslotFree) {
        if (!B_003E0EA4 || B_002DD2C4 >= 4) CGc_Collect(&g_2dd598);
        if (!B_00452148.pslotFree) {
            void *chunk = PvAllocSlotheapImpl(&B_00452148);
            if (B_002DD2C4) FreeSlotheapPv(&B_00452148, chunk);
            B_00452138[B_002DD2C4++] = chunk;
        }
    }
    SIDEBAG *psidebag = (SIDEBAG *)PvAllocSlotheapImpl(&B_00452148);
    InitSidebagNode(psidebag);
    psidebag->pvarb = 0;
    return psidebag;
}
}

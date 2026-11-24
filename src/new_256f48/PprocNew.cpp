// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
struct PROC {
    u8 unknown_0x0[0x8];
    s32 frame;
    u8 unknown_0xC[0x8];
    s32 params;
    s32 body;
};
extern "C" {
void *PvAllocSlotheapImpl(SLOTHEAP *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void CGc_Collect(void *);
void InitProcNode(void *);
extern SLOTHEAP B_00452120;
extern void *B_00452110[];
extern unsigned B_002DD2B4;
extern int B_003E0EA4;
extern char g_2dd598;
PROC *PprocNew(void)
{
    if (!B_00452120.pslotFree) {
        if (!B_003E0EA4 || B_002DD2B4 >= 4) CGc_Collect(&g_2dd598);
        if (!B_00452120.pslotFree) {
            void *chunk = PvAllocSlotheapImpl(&B_00452120);
            if (B_002DD2B4) FreeSlotheapPv(&B_00452120, chunk);
            B_00452110[B_002DD2B4++] = chunk;
        }
    }
    PROC *p = (PROC *)PvAllocSlotheapImpl(&B_00452120);
    InitProcNode(p);
    p->frame = 0;
    p->params = 0;
    p->body = 0;
    return p;
}
}

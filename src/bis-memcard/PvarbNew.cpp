// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
#include "sidebag.h"
extern "C" {
void *PvAllocSlotheapImpl(SLOTHEAP *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void CGc_Collect(void *);
void InitVarbNode(void *);
extern SLOTHEAP B_004520D0;
extern void *B_004520C0[];
extern unsigned B_002DD294;
extern int B_003E0EA4;
extern char g_2dd598;
void *PvarbNew(void)
{
    if (!B_004520D0.pslotFree) {
        if (!B_003E0EA4 || B_002DD294 >= 4) CGc_Collect(&g_2dd598);
        if (!B_004520D0.pslotFree) {
            void *chunk = PvAllocSlotheapImpl(&B_004520D0);
            if (B_002DD294) FreeSlotheapPv(&B_004520D0, chunk);
            B_004520C0[B_002DD294++] = chunk;
        }
    }
    VARB *pvarb = (VARB *)PvAllocSlotheapImpl(&B_004520D0);
    InitVarbNode(pvarb);
    pvarb->ref.m_tagk = TAGK_Nil;
    pvarb->pvarbNext = 0;
    return pvarb;
}
}

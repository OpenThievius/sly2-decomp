/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "sw.h"
struct FRAMENODE {
    u8 unknown_0x0[0xC];
    /* 0xC */ s32 aiWord[4]; /* reader: PframeNew (zeroed) */
    /* 0x1C */ s32 iWord1C;  /* reader: PframeNew (zeroed) */
};
extern "C" {
void *PvAllocSlotheapImpl(SLOTHEAP *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void CGc_Collect(void *);
void InitFrameNode(void *);
extern SLOTHEAP B_004520F8;
extern void *B_004520E8[];
extern unsigned B_002DD2A4;
extern int B_003E0EA4;
extern char g_2dd598;
void *PframeNew(void)
{
    if (!B_004520F8.pslotFree) {
        if (!B_003E0EA4 || B_002DD2A4 >= 4) CGc_Collect(&g_2dd598);
        if (!B_004520F8.pslotFree) {
            void *chunk = PvAllocSlotheapImpl(&B_004520F8);
            if (B_002DD2A4) FreeSlotheapPv(&B_004520F8, chunk);
            B_004520E8[B_002DD2A4++] = chunk;
        }
    }
    FRAMENODE *p = (FRAMENODE *)PvAllocSlotheapImpl(&B_004520F8);
    InitFrameNode(p);
    int *q = p->aiWord;
    int n = 3;
    do { *q++ = 0; } while (--n != -1);
    p->iWord1C = 0;
    return p;
}
}

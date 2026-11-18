// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"

struct LIGHT { u8 unknown_0x0[0x120]; int block[12]; };
struct PACKETSTATE { u8 unknown_0x0[0xC]; u32 *pwrite; };
struct LIGHTLIST { u8 unknown_0x0[0x14]; int cwordBlocks; u32 *pstart; };

extern PACKETSTATE g_2dea28;
extern int D_002BFC60[12];
void RebuildLight(LIGHT *plight);

static inline void AppendBlock(int icommand, const int *psource)
{
    *g_2dea28.pwrite = 0x6C03C000 | icommand;
    g_2dea28.pwrite = g_2dea28.pwrite + 1;
    u32 *pdest = g_2dea28.pwrite;
    for (int iword = 0; iword < 12; iword += 4) {
        int word0 = psource[iword];
        int word1 = psource[iword + 1];
        int word2 = psource[iword + 2];
        int word3 = psource[iword + 3];
        pdest[iword] = word0;
        pdest[iword + 1] = word1;
        pdest[iword + 2] = word2;
        pdest[iword + 3] = word3;
    }
    g_2dea28.pwrite += 12;
}

void func_001A4AD8(void *unused, int clight, LIGHT **pplight, LIGHTLIST *plist)
{
    int ilight = 0;
    plist->pstart = g_2dea28.pwrite;
    for (; ilight < clight; ilight++) {
        LIGHT *plight = pplight[ilight];
        RebuildLight(plight);
        AppendBlock(ilight * 3 + 0x15, plight->block);
    }
    for (; ilight < 4; ilight++)
        AppendBlock(ilight * 3 + 0x15, D_002BFC60);
    plist->cwordBlocks = ((char *)g_2dea28.pwrite - (char *)plist->pstart) >> 4;
}

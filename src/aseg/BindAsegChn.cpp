// SPDX-License-Identifier: GPL-3.0-or-later
#include "alo.h"
#include "asega.h"
#include "sw.h"
#include "xf.h"

extern "C" SO *PloFindSwObject_thunk(SW *, int, int, void *);
extern "C" SW B_003DD490;

extern "C" void BindAsegChn(ASEG *paseg, ALO *paloRoot, ASEGCHN *pchn, SO **ppso, XF **ppxf)
{
    if (paloRoot != 0)
        *ppso = PloFindSwObject_thunk(&B_003DD490, 1, (s32)(pchn->grf << 12) >> 12, paloRoot);
    else
        *ppso = PloFindSwObject_thunk(&B_003DD490, 4, (s32)(pchn->grf << 12) >> 12, paseg);
    if (*ppso == 0)
        *ppxf = 0;
    else
        *ppxf = (XF *)(*ppso)->PxfFromRef((s32)(pchn->grf << 2) >> 22);
}

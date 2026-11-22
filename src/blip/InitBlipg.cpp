// SPDX-License-Identifier: GPL-3.0-or-later
#include "blip.h"
extern "C" void InitXfm(BLIPG *);
extern "C" void InitDl__FP2DLi(DL *, int);
extern "C" void func_001A6CA8(BLIPG *, int);
void InitBlipg(BLIPG *pblipg)
{
    InitXfm(pblipg);
    InitDl__FP2DLi(&pblipg->dlBlips, 0x1090);
    pblipg->oid = -1;
    pblipg->field_0x38 = 1.0e10f;
    func_001A6CA8(pblipg, 1);
    u32 grf = pblipg->grfSw;
    if (((grf ^ 1) & 1) != 0) {
        GRFENTRY *pgrfentry = (GRFENTRY *)grf;
        pgrfentry->grf = (pgrfentry->grf & 1) | 0xe;
    } else {
        pblipg->grfSw = (grf & 1) | 0xe;
    }
}

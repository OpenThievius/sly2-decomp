// SPDX-License-Identifier: GPL-3.0-or-later
#include "asega.h"

void InitDl(DL *, int);

extern "C" {
void InitLo();

void InitAseg__FP4ASEG(ASEG *paseg)
{
    InitLo();
    InitDl(&paseg->dlAsega, 0x2C);
    CLQ *pclq = &paseg->clqSpeed;
    paseg->svtMaster = 1.0f;
    pclq->g0 = 1.0f;
    pclq->g1 = 0.0f;
    pclq->g2 = 0.0f;
    paseg->lmSpeed.gMax = 1.0f;
    paseg->lmSpeed.gMin = 0.0f;
    paseg->grfSw |= 0x40;
}
}

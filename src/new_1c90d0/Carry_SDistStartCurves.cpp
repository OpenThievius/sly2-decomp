// SPDX-License-Identifier: GPL-3.0-or-later
#include "carrypart.h"

extern "C" void func_001CC168(CARRYPART *pcarry, float u, QW pos, float *pu, float *ps);

extern "C" float Carry_SDistStartCurves(CARRYPROBE *pprobe, float u)
{
    float dist;
    func_001CC168(pprobe->pcarry, u, pprobe->posFlat, 0, &dist);
    return dist;
}

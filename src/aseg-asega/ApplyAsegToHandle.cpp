// SPDX-License-Identifier: GPL-3.0-or-later
#include "alo.h"
#include "asega.h"

extern "C" void RetractAsegaHandle(ASEGA **);
extern "C" void ApplyAseg(ASEG *, ALO *, float, float, int, ASEGA **);

extern "C" void ApplyAsegToHandle(ASEG *paseg, ALO *paloRoot, int grfapl, ASEGA **ppasega, float tLocal, float svtLocal)
{
    RetractAsegaHandle(ppasega);
    if (paseg != 0) {
        ApplyAseg(paseg, paloRoot, tLocal, svtLocal, grfapl, ppasega);
        (*ppasega)->OnAdd();
    }
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "asega.h"
#include "sw.h"

extern "C" LO *PloFindSwObject_thunk(SW *, int, int, void *);
extern "C" SW B_003DD490;
extern "C" void func_00130010(ASEG *paseg, LO *ploRoot, ASEGPART *ppart, LO **pplo, unsigned *pnTarget)
{
    if (ploRoot != 0) *pplo = PloFindSwObject_thunk(&B_003DD490, 1, ppart->oid, ploRoot);
    else *pplo = PloFindSwObject_thunk(&B_003DD490, 4, ppart->oid, paseg);
    if (*pplo == 0) *pnTarget = 0;
    else *pnTarget = (*pplo)->FReturnFalse(ppart->ipart);
}

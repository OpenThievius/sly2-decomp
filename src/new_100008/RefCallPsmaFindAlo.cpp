// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "lo.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" BASIC *PsmaFindAlo(LO *, int);

extern "C" CRef RefCallPsmaFindAlo(LO *object, int count, CRef *args)
{
    int aotyp = 6;
    int oid;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &oid);
    refResult.SetBasic(PsmaFindAlo(object, oid));
    return refResult;
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "lo.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" BASIC *PasegaFindAlo(LO *, int);

extern "C" CRef RefCallPasegaFindAlo(LO *object, int count, CRef *args)
{
    int aotyp = 6;
    int oid;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &oid);
    refResult.SetBasic(PasegaFindAlo(object, oid));
    return refResult;
}

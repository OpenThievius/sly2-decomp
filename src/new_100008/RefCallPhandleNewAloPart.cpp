// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" BASIC *func_001F85E0(BASIC *, int);

extern "C" CRef RefCallPhandleNewAloPart(BASIC *object, int count, CRef *args)
{
    int aotyp = 6;
    int oid;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &oid);
    refResult.SetBasic(func_001F85E0(object, oid));
    return refResult;
}

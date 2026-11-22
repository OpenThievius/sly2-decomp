// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct SMA;
extern "C" float DtSmaReachState(SMA *, int);

extern "C" CRef RefCallTimeToGoal(SMA *object, int count, CRef *args)
{
    int aotyp = 6;
    int oid;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &oid);
    refResult.SetF32(DtSmaReachState(object, oid));
    return refResult;
}

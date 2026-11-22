// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "stepguard.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" int FIsGuardInSgs(STEPGUARD *, int);

extern "C" CRef func_00103AB8(STEPGUARD *object, int count, CRef *args)
{
    int aotyp = 0x1010;
    int sgs;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &sgs);
    refResult.SetBool(FIsGuardInSgs(object, sgs) != 0);
    return refResult;
}


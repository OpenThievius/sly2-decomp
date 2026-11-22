// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" int FCanLease(BASIC *);

extern "C" CRef RefCallFCanLease(BASIC *object, int count, CRef *args)
{
    CRef refResult = RefSetArgsFromSplice(0, args, 0);
    refResult.SetBool(FCanLease(object) != 0);
    return refResult;
}

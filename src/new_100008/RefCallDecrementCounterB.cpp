// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void DecrementCounterB_1feec0(BASIC *);

extern "C" CRef RefCallDecrementCounterB(BASIC *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    DecrementCounterB_1feec0(object);
    return refResult;
}


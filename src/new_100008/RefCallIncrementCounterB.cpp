// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct SNDMANAGER;
extern "C" void IncrementCounterB_1feeb0(SNDMANAGER *);

extern "C" CRef RefCallIncrementCounterB(SNDMANAGER *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    IncrementCounterB_1feeb0(object);
    return refResult;
}

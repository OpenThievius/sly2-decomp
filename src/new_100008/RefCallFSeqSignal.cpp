// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct SGG;
extern "C" int FSggHasAlarm(SGG *, int);

extern "C" CRef RefCallFSeqSignal(SGG *object, int count, CRef *args)
{
    int aotyp = 6;
    int alarm;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &alarm);
    refResult.SetBool(FSggHasAlarm(object, alarm) != 0);
    return refResult;
}


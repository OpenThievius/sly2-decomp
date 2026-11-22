// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "murray.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void StartMurrayFlop(MURRAY *);

extern "C" CRef RefCallStartMurrayFlop(MURRAY *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    StartMurrayFlop(object);
    return refResult;
}

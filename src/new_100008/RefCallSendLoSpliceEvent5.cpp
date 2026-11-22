// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "lo.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void EnableLasen__FP5LASEN5SENSM(LO *);

extern "C" CRef RefCallSendLoSpliceEvent5(LO *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    EnableLasen__FP5LASEN5SENSM(object);
    return refResult;
}

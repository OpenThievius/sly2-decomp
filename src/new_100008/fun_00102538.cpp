// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" float MarkClockTickRealOnly__FP5CLOCK(BASIC *);

extern "C" CRef func_00102538(BASIC *object, int count, CRef *args)
{
    CRef refResult = RefSetArgsFromSplice(0, args, 0);
    refResult.SetF32(MarkClockTickRealOnly__FP5CLOCK(object));
    return refResult;
}


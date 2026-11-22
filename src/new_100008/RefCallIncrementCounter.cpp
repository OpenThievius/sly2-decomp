// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct SNDMANAGER;
extern "C" void func_001FEE90(SNDMANAGER *);

extern "C" CRef RefCallIncrementCounter(SNDMANAGER *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_001FEE90(object);
    return refResult;
}

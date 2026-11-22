// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "stepguard.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void func_001B9CA0(STEPGUARD *, int);

extern "C" CRef RefCallResetMurrayGoalStack(STEPGUARD *object, int count, CRef *args)
{
    int aotyp = 0;
    int fResetGoalStack;
    RefSetArgsFromSplice(1, args, &aotyp, &fResetGoalStack);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_001B9CA0(object, fResetGoalStack);
    return refResult;
}

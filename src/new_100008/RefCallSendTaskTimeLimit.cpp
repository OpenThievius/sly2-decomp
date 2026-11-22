// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct TASK;
extern "C" void SendTaskTimeLimit(TASK *, int);

extern "C" CRef RefCallSendTaskTimeLimit(TASK *object, int count, CRef *args)
{
    int aotyp = 0;
    int timeLimit;
    RefSetArgsFromSplice(1, args, &aotyp, &timeLimit);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SendTaskTimeLimit(object, timeLimit);
    return refResult;
}

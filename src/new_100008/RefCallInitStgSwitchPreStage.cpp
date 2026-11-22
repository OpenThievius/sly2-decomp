// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct STGSWITCH;
extern "C" void InitStgSwitchPreStage(STGSWITCH *);

extern "C" CRef RefCallInitStgSwitchPreStage(STGSWITCH *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    InitStgSwitchPreStage(object);
    return refResult;
}

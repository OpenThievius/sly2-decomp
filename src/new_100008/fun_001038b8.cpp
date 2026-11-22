// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "stepguard.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void ClearGuardIgnoredClasses(STEPGUARD *);

extern "C" CRef func_001038B8(STEPGUARD *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    ClearGuardIgnoredClasses(object);
    return refResult;
}


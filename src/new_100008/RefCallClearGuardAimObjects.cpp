// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "stepguard.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void ClearGuardAimObjects(STEPGUARD *);

extern "C" CRef RefCallClearGuardAimObjects(STEPGUARD *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    ClearGuardAimObjects(object);
    return refResult;
}


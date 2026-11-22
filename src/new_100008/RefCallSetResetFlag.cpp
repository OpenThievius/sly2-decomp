// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "cm.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
void SetResetFlag(CM *);

extern "C" CRef RefCallSetResetFlag(CM *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SetResetFlag(object);
    return refResult;
}

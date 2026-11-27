// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "stepguard.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);

/* STEPGUARD61, class 61: stepguard.h */
CRef RefCallSlot2D0(STEPGUARD61 *object, int count, CRef *args)
{
    int aotyp = 0;
    int arg;
    RefSetArgsFromSplice(1, args, &aotyp, &arg);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    object->Slot90(arg);
    return refResult;
}

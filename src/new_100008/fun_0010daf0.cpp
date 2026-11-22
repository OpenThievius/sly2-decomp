// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "so.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);

CRef func_0010DAF0(SO *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    object->Slot49(-1);
    return refResult;
}

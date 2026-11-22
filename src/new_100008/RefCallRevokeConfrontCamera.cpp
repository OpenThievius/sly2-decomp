// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct JSG;
extern "C" void AddSeqRecordRevokeConfrontCamera(JSG *, int);

extern "C" CRef RefCallRevokeConfrontCamera(JSG *object, int count, CRef *args)
{
    int aotyp = 0;
    int value;
    RefSetArgsFromSplice(1, args, &aotyp, &value);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    AddSeqRecordRevokeConfrontCamera(object, value);
    return refResult;
}

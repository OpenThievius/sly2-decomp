// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void *AddSeqRecordHideBinoc(BASIC *, int);

extern "C" CRef RefCallHideBinoc(BASIC *object, int count, CRef *args)
{
    int aotyp = 0;
    int hide;
    RefSetArgsFromSplice(1, args, &aotyp, &hide);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    AddSeqRecordHideBinoc(object, hide);
    return refResult;
}


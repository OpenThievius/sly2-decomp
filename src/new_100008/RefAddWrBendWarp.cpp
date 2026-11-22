// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct WR;
extern "C" void AddWrBendWarp__FP2WR(WR *);

extern "C" CRef RefAddWrBendWarp(WR *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    AddWrBendWarp__FP2WR(object);
    return refResult;
}


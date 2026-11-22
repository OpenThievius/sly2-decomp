// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct ASEGA;
extern "C" void SnapAsega(ASEGA *, int);

extern "C" CRef RefCallSnapAsega(ASEGA *object, int count, CRef *args)
{
    int aotyp = 0;
    int snap;
    RefSetArgsFromSplice(1, args, &aotyp, &snap);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SnapAsega(object, snap);
    return refResult;
}

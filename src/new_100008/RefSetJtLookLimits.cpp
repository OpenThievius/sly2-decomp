// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { int b[3]; };
extern "C" const AOT RO_002A3EC0;
extern "C" void SetJtLookLimits(BASIC *, VECTOR *, VECTOR *, VECTOR *);
CRef RefSetJtLookLimits(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3EC0;
    VECTOR a, b, c;
    RefSetArgsFromSplice(3, args, &aotyp, &a, &b, &c);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SetJtLookLimits(object, &a, &b, &c);
    return refResult;
}

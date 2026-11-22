// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { int v[2]; };
extern "C" const AOT RO_002A3B78;
extern "C" void SetGuardGotoTarget(BASIC *, int, QW);

CRef func_00103F40(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3B78;
    int first;
    VECTOR second;
    RefSetArgsFromSplice(2, args, &aotyp, &first, &second);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SetGuardGotoTarget(object, first, *(QW *)&second);
    return refResult;
}

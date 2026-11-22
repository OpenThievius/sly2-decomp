// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { char b[8]; };
extern "C" const AOT RO_002A3B78;
extern "C" void func_00142540(BASIC *, int, QW);
CRef RefCallSetJtScriptGoal(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3B78;
    int a;
    VECTOR b;
    RefSetArgsFromSplice(2, args, &aotyp, &a, &b);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_00142540(object, a, *(QW *)&b);
    return refResult;
}

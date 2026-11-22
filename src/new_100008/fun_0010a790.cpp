// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { char b[8]; int w; };
extern "C" void func_00141968(BASIC *, QW, float, float);
extern const AOT RO_002A3EA0;
CRef func_0010A790(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3EA0;
    VECTOR q;
    float x, y;
    RefSetArgsFromSplice(3, args, &aotyp, &q, &x, &y);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_00141968(object, *(QW *)&q, x, y);
    return refResult;
}

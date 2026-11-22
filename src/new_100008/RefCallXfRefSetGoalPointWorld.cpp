// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { int w[3]; };
extern "C" void func_001F8A78(BASIC *, int, int, QW);
extern const AOT RO_002A3F90;
CRef RefCallXfRefSetGoalPointWorld(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3F90;
    int a, b;
    VECTOR vec;
    RefSetArgsFromSplice(3, args, &aotyp, &a, &b, &vec);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_001F8A78(object, a, b, *(QW *)&vec);
    return refResult;
}

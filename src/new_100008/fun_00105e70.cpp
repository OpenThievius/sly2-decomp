// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
extern "C" void func_00170BA0(BASIC *, void *);
CRef func_00105E70(BASIC *object, int count, CRef *args)
{
    int aotyp[1] = {0xA};
    VECTOR value;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_00170BA0(object, &value);
    return refResult;
}

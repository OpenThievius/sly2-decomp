// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" int func_00171DA8(BASIC *, BASIC *);

extern "C" CRef func_00103EC0(BASIC *object, int count, CRef *args)
{
    int aotyp = 0x2071;
    BASIC *link;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &link);
    refResult.SetBool(func_00171DA8(object, link) != 0);
    return refResult;
}


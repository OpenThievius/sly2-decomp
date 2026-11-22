// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" int func_001841F0(BASIC *, BASIC *);

extern "C" CRef RefCallFStateAccepted(BASIC *object, int count, CRef *args)
{
    int aotyp = 0x2002;
    BASIC *other;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &other);
    refResult.SetBool(func_001841F0(object, other) != 0);
    return refResult;
}


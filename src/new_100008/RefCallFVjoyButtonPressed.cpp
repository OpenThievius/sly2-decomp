// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" int FVjoyButtonPressed(BASIC *, int);

extern "C" CRef RefCallFVjoyButtonPressed(BASIC *object, int count, CRef *args)
{
    int aotyp = 5;
    int button;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &button);
    refResult.SetBool(FVjoyButtonPressed(object, button) != 0);
    return refResult;
}


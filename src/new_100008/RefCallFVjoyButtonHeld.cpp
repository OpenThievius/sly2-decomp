// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct VJOY;
extern "C" int FVjoyButtonHeld(VJOY *, int);

extern "C" CRef RefCallFVjoyButtonHeld(VJOY *object, int count, CRef *args)
{
    int aotyp = 5;
    int button;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &button);
    refResult.SetBool(FVjoyButtonHeld(object, button) != 0);
    return refResult;
}

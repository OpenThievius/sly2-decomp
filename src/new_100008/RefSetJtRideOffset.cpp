// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
extern "C" void SetJtRideOffset(BASIC *, QW);
CRef RefSetJtRideOffset(BASIC *object, int count, CRef *args)
{
    int aotyp[1] = {2};
    VECTOR vec;
    RefSetArgsFromSplice(1, args, aotyp, &vec);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SetJtRideOffset(object, *(QW *)&vec);
    return refResult;
}

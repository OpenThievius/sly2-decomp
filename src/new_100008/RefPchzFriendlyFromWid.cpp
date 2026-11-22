// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "guard.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" int NGetSensorLoState(SENSOR *, int);

extern "C" CRef RefPchzFriendlyFromWid(SENSOR *object, int count, CRef *args)
{
    int aotyp = 0x2002;
    int wid;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &wid);
    refResult.SetS32(NGetSensorLoState(object, wid));
    return refResult;
}

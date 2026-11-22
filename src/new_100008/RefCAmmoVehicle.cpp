// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct VEHICLE;
extern "C" int func_001D4D00(VEHICLE *, int);

extern "C" CRef RefCAmmoVehicle(VEHICLE *object, int count, CRef *args)
{
    int aotyp = 0x1065;
    int gunIndex;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &gunIndex);
    refResult.SetS32(func_001D4D00(object, gunIndex));
    return refResult;
}

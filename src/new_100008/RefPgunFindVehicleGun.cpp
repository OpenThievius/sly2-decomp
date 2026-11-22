// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct VEHICLE;
extern "C" BASIC *func_001D3FA8(VEHICLE *, int);

extern "C" CRef RefPgunFindVehicleGun(VEHICLE *object, int count, CRef *args)
{
    int aotyp = 6;
    int id;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &id);
    refResult.SetBasic(func_001D3FA8(object, id));
    return refResult;
}

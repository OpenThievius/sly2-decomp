// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct VEHICLEGUN;
extern "C" void SpendVehicleGunAmmo(VEHICLEGUN *);

extern "C" CRef RefSpendVehicleGunAmmo(VEHICLEGUN *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SpendVehicleGunAmmo(object);
    return refResult;
}

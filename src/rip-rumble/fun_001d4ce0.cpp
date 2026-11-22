// SPDX-License-Identifier: GPL-3.0-or-later
#include "vehicle.h"

void func_001D4CE0(VEHICLE *vehicle, int index, int ammoType, float bias)
{
    VEHICLEAMMO *ammo = vehicle->aammo + index;
    ammo->ammoType = ammoType;
    ammo->bias = bias;
}

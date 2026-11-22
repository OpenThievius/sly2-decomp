/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "vehicle.h"

void func_001D4D18(struct VEHICLE *vehicle, s32 index, s32 cammo) {
    vehicle->aammo[index].cammo = cammo;
}

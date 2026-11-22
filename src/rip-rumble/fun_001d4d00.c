/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "vehicle.h"

s32 func_001D4D00(struct VEHICLE *vehicle, s32 index) {
    return vehicle->aammo[index].cammo;
}

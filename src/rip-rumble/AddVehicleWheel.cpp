// SPDX-License-Identifier: GPL-3.0-or-later
#include "vehicle.h"
extern "C" {
void AddVehicleWheel(VEHICLE *vehicle, s32 oid, BYTES8 *field_0x24, f32 radius) {
    u32 count = vehicle->cwheel;
    if (count < 8U) {
        vehicle->cwheel = count + 1;
        VEHICLEWHEEL *wheel = vehicle->awheel + count;
        wheel->oid = oid;
        wheel->radius = radius;
        wheel->field_0x24 = *field_0x24;
    }
}
}

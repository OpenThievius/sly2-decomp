/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "vehicle.h"

void OnPoActive(struct VEHICLE *vehicle, s32 fActive);
void SetVehicleState(struct VEHICLE *vehicle, s32 state);

void OnVehicleActive(struct VEHICLE *vehicle, s32 fActive) {
    OnPoActive(vehicle, fActive);
    if (fActive != 0) {
        SetVehicleState(vehicle, 2);
    } else if (vehicle->state == 2) {
        SetVehicleState(vehicle, 0);
    }
}

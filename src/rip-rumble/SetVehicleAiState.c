/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "vehicle.h"
#include "clock.h"

void SetVehicleAiState(struct VEHICLE *vehicle, s32 aiState) {
    if (aiState != vehicle->aiState) {
        vehicle->aiState = aiState;
        vehicle->tAiState = g_2dded0.t;
    }
}

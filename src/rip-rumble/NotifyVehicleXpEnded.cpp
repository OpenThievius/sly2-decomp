// SPDX-License-Identifier: GPL-3.0-or-later
#include "vehicle.h"
extern "C" {
void func_001F4DA8(VEHICLE *vehicle, SO *pso, void **ppxps);
void func_001F5988(VEHICLE *vehicle, SO *pso);

void NotifyVehicleXpEnded(VEHICLE *vehicle, SO *pso) {
    func_001F5988(vehicle, pso);
    for (s32 index = 0; index < vehicle->cwheel; index++) {
        func_001F4DA8(vehicle, pso, &vehicle->awheel[index].pxps);
    }
}

}

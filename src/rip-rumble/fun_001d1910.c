/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "vehicle.h"

void func_001CB518(struct VEHICLE *vehicle, void *pool);
void func_001D14C0(struct VEHICLE *vehicle);

void func_001D1910(struct VEHICLE *vehicle, void *pool) {
    func_001CB518(vehicle, pool);
    func_001D14C0(vehicle);
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "vehicle.h"
#include "geom.h"
#include "oxa.h"
extern "C" void func_001F5990(VEHICLE *vehicle, GEOM *geom, int cbsp, void *absp, void *pbspLast);
extern "C" void func_001D3450(VEHICLE *vehicle, VEHICLEWHEEL *wheel, GEOM *geom, int cbsp, void *absp, void *pbspLast, void **ppxps);

void AddVehicleCustomXps(VEHICLE *vehicle, GEOM *geom, int cbsp, void *absp, void *pbspLast)
{
    func_001F5990(vehicle, geom, cbsp, absp, pbspLast);
    SO *other = geom->pso->poxa->owner;
    if (other->FIsLocked() != 0) {
        for (int index = 0; index < vehicle->cwheel; index++) {
            VEHICLEWHEEL *wheel = vehicle->awheel + index;
            func_001D3450(vehicle, wheel, geom, cbsp, absp, pbspLast, &wheel->pxps);
        }
    }
}

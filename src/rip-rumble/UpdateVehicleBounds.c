/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "vehicle.h"

struct SO;
QW ConvertAloPos(struct SO *, long, QW);
void ExtendSoBounds(struct SO *, QW, f32);
void UpdateSoBounds(struct SO *);

void UpdateVehicleBounds(struct VEHICLE *vehicle) {
    s32 index = 0;
    UpdateSoBounds((struct SO *)vehicle);
    if (vehicle->cwheel > 0) {
        struct VEHICLEWHEEL *wheel = vehicle->awheel;
        do {
            QW pos;
            index += 1;
            pos = ConvertAloPos((struct SO *)vehicle, 0, wheel->pos);
            ExtendSoBounds((struct SO *)vehicle, pos, wheel->radius);
            wheel += 1;
        } while (index < vehicle->cwheel);
    }
}

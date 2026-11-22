/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "vehicle.h"

#include "sma.h"

/* the SMA's state machine: a pointer to the goal id at 0x54 (this function's view: one reader) */
struct SM {
    u8 unknown_0x0[0x54];
    s32 *poidGoal;
};

void SetVehicleState(struct VEHICLE *vehicle, s32 state);
void SnapSmaToGoal(struct SMA *psma, s32 oidGoal);
void UpdateVehicleHpBlot(struct VEHICLE *vehicle);

void func_001D14C0(struct VEHICLE *vehicle) {
    struct SMA *psma;

    vehicle->hp = vehicle->hpMax;
    UpdateVehicleHpBlot(vehicle);
    psma = vehicle->psma;
    if (psma != 0) {
        SnapSmaToGoal(psma, *psma->psm->poidGoal);
    }
    SetVehicleState(vehicle, 0);
}

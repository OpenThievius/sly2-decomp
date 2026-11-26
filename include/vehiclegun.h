/* SPDX-License-Identifier: GPL-3.0-or-later */
/* VEHICLEGUN, one of a vehicle's guns (VEHICLE::apgun, 0xB0 bytes): the vehicle it belongs to, the Sma it drives, the two button masks
   that fire it and the ammunition slot and cost of a shot. CopyVehicleGun copies the block from 0x14 on (0x9C bytes). Fields from
   the readers named; func_001D2150 reads sma and the masks on a gun it also passes to FVehicleGunHasAmmo (so it is this class).
   C++ only. */
#ifndef SLY2_VEHICLEGUN_H
#define SLY2_VEHICLEGUN_H
#include "types.h"
#include "vehicle.h"

struct VEHICLEGUN {
    u8 unknown_0x0[0x10];
    /* 0x10 */ VEHICLE *pvehicle; /* readers: FVehicleGunHasAmmo, SpendVehicleGunAmmo (its ammunition slot) */
    /* 0x14 */ u8 field_0x14[0xC]; /* CopyVehicleGun copies this block and the words after it (0x9C bytes in all) */
    /* 0x20 */ struct SMA *sma;   /* reader: func_001D2150 (SetSmaGoal 0x67 when it fires, 0x68 on a press) */
    /* 0x24 */ u32 heldMask;      /* func_001D2150 tests the stick's held buttons against it */
    /* 0x28 */ s32 pressedMask;   /* func_001D2150 passes it to FButtonPressedWithin */
    u8 field_0x2C[0x40];
    /* 0x6C */ s32 iammo;         /* the ammunition slot: FVehicleGunHasAmmo, SpendVehicleGunAmmo */
    /* 0x70 */ s32 cost;          /* what a shot takes: FVehicleGunHasAmmo (needs it), SpendVehicleGunAmmo (spends it) */
    u8 unknown_0x74[0x3C];
};
#endif

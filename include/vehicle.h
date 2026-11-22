/* SPDX-License-Identifier: GPL-3.0-or-later */
/* VEHICLE, a drivable vehicle (retail's InitVehicle, SetVehicleState, AddVehicleWheel ... and the Ref bindings that call them):
   a PO (include/po.h) whose own fields start at 0x180. Only the fields the readers named below use are declared; the rest are
   sized gaps. In C the PO part is a plain gap. C and C++. */
#ifndef SLY2_VEHICLE_H
#define SLY2_VEHICLE_H
#include "types.h"
#include "bytes8.h"
#ifdef __cplusplus
#include "po.h"
#endif

struct LO;

/* one of the vehicle's wheels, 0x60 bytes (AddVehicleWheel fills the next one from a script's arguments) */
struct VEHICLEWHEEL {
    /* 0x00 */ s32 oid;          /* AddVehicleWheel (the script's object id) */
    u8 unknown_0x4[0x4];
    /* 0x08 */ void *pxps;       /* the head of the wheel's contact list: AddVehicleCustomXps and NotifyVehicleXpEnded pass its address
                                  (func_001F4DA8 walks and unlinks it) */
    u8 unknown_0xC[0x14];
    /* 0x20 */ f32 radius;       /* AddVehicleWheel (the script's radius), UpdateVehicleBounds (extends the bounds by it) */
    /* 0x24 */ struct BYTES8 field_0x24; /* AddVehicleWheel copies the script's eight bytes */
    u8 unknown_0x2C[0x24];
    /* 0x50 */ QW pos;           /* UpdateVehicleBounds (converted with ConvertAloPos, extends the bounds) */
};

/* one ammunition slot, 0xC bytes (RefSetVehicleAmmo, RefSetVehicleAmmoType, RefCAmmoVehicle go through the three functions) */
struct VEHICLEAMMO {
    /* 0x0 */ s32 cammo;         /* func_001D4D00 returns it, func_001D4D18 sets it, FVehicleGunHasAmmo and SpendVehicleGunAmmo use it */
    /* 0x4 */ s32 ammoType;      /* func_001D4CE0 sets it (RefSetVehicleAmmoType's second argument) */
    /* 0x8 */ f32 bias;          /* func_001D4CE0 sets it; func_001D22D0 adds it to a target's distance */
};

#ifdef __cplusplus
struct VEHICLE : PO {
#else
struct VEHICLE {
    u8 unknown_0x0[0x180]; /* a PO in C++ */
#endif
    /* 0x180 */ s32 state;       /* OnVehicleActive (2 is driven), SetVehicleState */
    u8 unknown_0x184[0x4];
    /* 0x188 */ s32 aiState;     /* SetVehicleAiState */
    /* 0x18C */ f32 tAiState;    /* SetVehicleAiState: the time of the change */
    /* 0x190 */ s32 cwheel;      /* AddVehicleWheel (at most 8), NotifyVehicleXpEnded, AddVehicleCustomXps, UpdateVehicleBounds */
    u8 unknown_0x194[0xC];
    /* 0x1A0 */ struct VEHICLEWHEEL awheel[8]; /* the same functions */
    u8 unknown_0x4A0[0xBC];
    /* 0x55C */ s32 hpMax;       /* func_001D14C0 copies it to hp; UpdateVehicleHpBlot divides by it */
    /* 0x560 */ s32 hp;          /* func_001D14C0 */
    u8 unknown_0x564[0xC];
    /* 0x570 */ struct SMA *psma; /* func_001D14C0 (snapped to its goal), SetVehicleState */
    /* 0x574 */ struct VEHICLEAMMO aammo[4]; /* func_001D4CE0, func_001D4D00, func_001D4D18, func_001D22D0 (index 4 and up unread) */
    u8 unknown_0x5A4[0x14];
    /* 0x5B8 */ struct LO *ploChase; /* func_001D22D0 (the target it prefers) */
};

#endif

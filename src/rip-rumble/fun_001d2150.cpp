#include "sly2.h"
struct SMA;
enum OID { OID_NONE };
struct JOY { u8 unknown_0x0[0x18]; float stick; u8 unknown_0x1C[0x30 - 0x1C]; unsigned held; };
struct GUN { u8 unknown_0x0[0x20]; SMA *sma; unsigned heldMask; int pressedMask; };
struct VEHICLE {
    u8 unknown_0x0[0x150]; JOY *joy; u8 unknown_0x154[0x4F8 - 0x154]; int cgun; GUN *apgun[8];
    float speedMax; u8 unknown_0x520[0x540 - 0x520]; float heading; float headingGoal; u8 unknown_0x548[4]; float aim; float speedGoal;
};
extern "C" int FVehicleGunHasAmmo(GUN *);
extern "C" int FButtonPressedWithin(JOY *, int, float);
void SetSmaGoal(SMA *, OID);

void func_001D2150(VEHICLE *vehicle)
{
    JOY *joy = vehicle->joy;
    float stick = joy->stick;
    vehicle->headingGoal = stick;
    if ((joy->held & 0x40) != 0) {
        vehicle->speedGoal = vehicle->speedMax;
        vehicle->aim = vehicle->heading;
    } else {
        vehicle->aim = stick;
        vehicle->speedGoal = 0.0f;
    }
    for (int index = 0; index < vehicle->cgun; index++) {
        GUN *gun = vehicle->apgun[index];
        if (!FVehicleGunHasAmmo(gun))
            continue;
        if ((vehicle->joy->held & gun->heldMask) != 0)
            SetSmaGoal(gun->sma, (OID)0x67);
        else if (FButtonPressedWithin(vehicle->joy, gun->pressedMask, 0.0f))
            SetSmaGoal(gun->sma, (OID)0x68);
    }
}

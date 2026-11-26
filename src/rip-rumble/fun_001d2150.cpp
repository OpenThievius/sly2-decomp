#include "sly2.h"
#include "joy.h"
#include "vehicle.h"
#include "vehiclegun.h"
enum OID { OID_NONE };
extern "C" int FVehicleGunHasAmmo(VEHICLEGUN *);
extern "C" int FButtonPressedWithin(JOY *, int, float);
void SetSmaGoal(SMA *, OID);

/* the drive words between 0x540 and 0x554: func_001D2150 is their one reader, so a local view of VEHICLE (vehicle.h) */
struct VEHICLEDRIVE {
    u8 unknown_0x0[0x540];
    /* 0x540 */ f32 heading;
    /* 0x544 */ f32 headingGoal;
    u8 unknown_0x548[0x4];
    /* 0x54C */ f32 aim;
    /* 0x550 */ f32 speedGoal;
};

void func_001D2150(VEHICLE *vehicle)
{
    JOY *joy = vehicle->pjoy;
    float stick = joy->radStick;
    ((VEHICLEDRIVE *)vehicle)->headingGoal = stick;
    if ((joy->grfbtn & 0x40) != 0) {
        ((VEHICLEDRIVE *)vehicle)->speedGoal = vehicle->speedMax;
        ((VEHICLEDRIVE *)vehicle)->aim = ((VEHICLEDRIVE *)vehicle)->heading;
    } else {
        ((VEHICLEDRIVE *)vehicle)->aim = stick;
        ((VEHICLEDRIVE *)vehicle)->speedGoal = 0.0f;
    }
    for (int index = 0; index < vehicle->cgun; index++) {
        VEHICLEGUN *gun = vehicle->apgun[index];
        if (!FVehicleGunHasAmmo(gun))
            continue;
        if ((vehicle->pjoy->grfbtn & gun->heldMask) != 0)
            SetSmaGoal(gun->sma, (OID)0x67);
        else if (FButtonPressedWithin(vehicle->pjoy, gun->pressedMask, 0.0f))
            SetSmaGoal(gun->sma, (OID)0x68);
    }
}

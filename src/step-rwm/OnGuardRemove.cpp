// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" const float RO_002A8610;
extern "C" int D_002C3CF0;
/* local view: 0xF0 and 0xF4 of the guard's SENSOR lie in its unknown block and only OnGuardRemove reads them */
struct SENSORVIEW_F0 { u8 unknown_0x0[0xF0]; s32 field_0xF0; s32 field_0xF4; };
void *memset(void *, int, unsigned int);
extern "C" void func_001CB5D0();
void ClearGuardPathMode(STEPGUARD *);
void ClearGuardSensing(STEPGUARD *);
void SetGuardMode(STEPGUARD *, int);
extern "C" void func_00208540(STEPGUARD *, int);
extern "C" void func_001F17F8(STEPGUARD *, int);

void OnGuardRemove(STEPGUARD *guard)
{
    func_001CB5D0();
    ClearGuardPathMode(guard);
    guard->field_0x2E8 = 0;
    memset(guard->scratch, 0, 0xC);
    guard->field_0xE94 = 0;
    ((SENSORVIEW_F0 *)guard->psensor)->field_0xF0 = 0;
    ((SENSORVIEW_F0 *)guard->psensor)->field_0xF4 = 0;
    guard->cguardact = 0;
    guard->iguardactCur = 0;
    guard->fActionDone = 0;
    guard->fEnabled = 0;
    guard->field_0xF94 = 0;
    guard->field_0xFA8 = 0;
    guard->field_0x390 = 0;
    func_00208540(guard, 0);
    ClearGuardSensing(guard);
    guard->field_0x330 = 0;
    guard->ptargetGoto = 0;
    guard->field_0xFC8 = 0;
    guard->field_0xFCC = 0;
    guard->field_0x360 = -10.0f;
    guard->field_0x4A0 = 1;
    guard->field_0xFF4 = RO_002A8610;
    guard->field_0x1000 = D_002C3CF0;
    func_001F17F8(guard, -1);
    SetGuardMode(guard, -1);
}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" int FIsGuardInSgs(void *, int);
/* local view: 0x298 lies in STEP's unknown block and only this method reads it */
struct STEPGUARDVIEW298 { u8 unknown_0x0[0x298]; s32 field_0x298; };
int FIsGuardInvulnerable(STEPGUARD *guard)
{
    if (guard->fDown || ((STEPGUARDVIEW298 *)guard)->field_0x298) return 1;
    return FIsGuardInSgs(guard, 0x2A) != 0;
}

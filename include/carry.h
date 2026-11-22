/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CARRY, the carry object Murray holds in MURRAY::ploCarried (include/murray.h): an LO whose word at 0x180 is the object it carries.
   Readers: StartMurrayLift, StartMurrayLiftGuard and DetachMurrayObject (as an SO), func_001B7AE8 and FMurrayCanUseGadget (as an LO,
   class tests and slot calls). C++ only. */
#ifndef SLY2_CARRY_H
#define SLY2_CARRY_H
#include "lo.h"
#include "so.h"

struct CARRY : LO {
    u8 unknown_0x50[0x130];
    /* 0x180 */ SO *pso; /* the carried object; DetachMurrayObject takes its transforms, StartMurrayLift hands it to func_002046F0 */
};
#endif

// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" {
u64 GrfsgsFromSgs(s32);
void SetGuardGrfsgs(STEPGUARD *, u64);
void RemoveGuardSgs(STEPGUARD *guard, s32 sgs) {
    SetGuardGrfsgs(guard, guard->grfsgs & ~GrfsgsFromSgs(sgs));
    s32 sgsNone = -1;
    s32 *argv[2];
    argv[0] = &sgsNone;
    argv[1] = &sgs;
    guard->HandleSpliceEvent(7, 0, 2, (s32)argv, 0);
}
}

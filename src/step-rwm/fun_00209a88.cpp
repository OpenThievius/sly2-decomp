// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" {
s32 AsgsFromGrfsgs(u64, s32 *);
void func_00200F58(void *, s32, s32, s32 *);

void *func_00209A88(void *presult, STEPGUARD *pguard) {
    s32 asgs[0x30] __attribute__((aligned(16)));
    func_00200F58(presult, AsgsFromGrfsgs(pguard->grfsgs, asgs), 0x1010, asgs);
    return presult;
}

}

// SPDX-License-Identifier: GPL-3.0-or-later
#include "murray.h"
#include "carry.h"
extern "C" {
void SetMurrayState(MURRAY *, int);
void func_002046F0(MURRAY *, SO *);

void StartMurrayLiftGuard(MURRAY *pmurray, LO *plo) {
    if (pmurray->field_0x13EC != 0) {
        pmurray->ploCarried = plo;
        pmurray->field_0x144C = 1;
        SetMurrayState(pmurray, 4);
        func_002046F0(pmurray, ((CARRY *)pmurray->ploCarried)->pso);
    }
}

}

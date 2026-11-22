/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void SetSearchState(struct GOALSEARCH *goal, s32 state);
void func_001EEF70(void);

void func_00171FA0(struct GOALSEARCH *goal) {
    func_001EEF70();
    SetSearchState(goal, 0);
}

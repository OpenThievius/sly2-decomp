/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void func_00175488(struct GOALREACT *goal, s32 state);
void func_001EEF70(void);
void func_001EEFC0(struct GOALREACT *goal);

void func_00175410(struct GOALREACT *goal) {
    func_001EEF70();
    func_00175488(goal, 0);
    func_001EEFC0(goal);
}

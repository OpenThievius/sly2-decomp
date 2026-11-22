/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goalpost.h"

void func_00155AE0(struct GOALPOSTWATCH *pgoal, s32 state);
void func_001EEF70(struct GOALPOSTWATCH *pgoal);

/* GoalPostWatch_Activate */
void func_00155A38(struct GOALPOSTWATCH *pgoal)
{
    func_001EEF70(pgoal);
    func_00155AE0(pgoal, 0);
}

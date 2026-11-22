/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "sly2.h"

void GoalHit_Deactivate(struct GOAL *pgoal);
void RecalcSwOxfFilterForObject(void *pworld, void *pobject);
extern u8 B_003DD490[];

void func_00179A20(struct GOAL *pgoal) {
    GoalHit_Deactivate(pgoal);
    RecalcSwOxfFilterForObject(B_003DD490, pgoal->pstep);
}

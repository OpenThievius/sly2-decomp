/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "sly2.h"

s32 FGoalAnimDone(void *pgoal);
void func_0017B750(struct GOAL *pgoal, s32 state);
void func_001EEF98(struct GOAL *pgoal);
s32 func_001EF0A8(struct GOAL *pgoal);

void func_0017B620(struct GOALSTAND *pgoal) {
    s32 statePrevious;

    func_001EEF98((struct GOAL *)pgoal);
loop_1:
    if (func_001EF0A8((struct GOAL *)pgoal) == 0) {
        statePrevious = pgoal->state;
        if ((statePrevious == 0) && (FGoalAnimDone(pgoal->pgoalChild) != 0)) {
            func_0017B750((struct GOAL *)pgoal, -1);
        }
        if (statePrevious != pgoal->state) {
            goto loop_1;
        }
    }
}

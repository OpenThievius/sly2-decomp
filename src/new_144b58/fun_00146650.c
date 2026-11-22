/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "clock.h"
#include "jtview.h"

void func_001EEFC0(struct GOALPARTNERATTACK *pgoal);
void func_001EF038(struct GOALPARTNERATTACK *pgoal);

void func_00146650(struct GOALPARTNERATTACK *pgoal, s32 state) {
    s32 stateOld = pgoal->state;
    if (state != stateOld) {
        if (stateOld == 2) {
            func_001EF038(pgoal);
        }
        pgoal->state = state;
        pgoal->tState = g_2dded0.t;
        if (state == 2) {
            func_001EEFC0(pgoal);
        }
    }
}

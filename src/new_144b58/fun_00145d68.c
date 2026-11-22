/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

void Goal_Deactivate(struct GOALPARTNERATTACK *pgoal);

void func_00145D68(struct GOALPARTNERATTACK *pgoal) {
    Goal_Deactivate(pgoal);
    GOAL_JT(pgoal)->fFocusBusy &= ~1;
}

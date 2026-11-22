/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

void Goal_Deactivate(struct GOALPARTNERFOLLOW *pgoal);
void func_00145B18(struct GOALPARTNERFOLLOW *pgoal, s32 state);

void func_001450B0(struct GOALPARTNERFOLLOW *pgoal) {
    Goal_Deactivate(pgoal);
    func_00145B18(pgoal, -1);
}

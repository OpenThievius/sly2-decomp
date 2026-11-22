/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

void func_001EEF70(struct GOALPARTNERFOLLOW *pgoal);
void func_00145B18(struct GOALPARTNERFOLLOW *pgoal, s32 state);

void func_00145080(struct GOALPARTNERFOLLOW *pgoal) {
    func_001EEF70(pgoal);
    func_00145B18(pgoal, 0);
}

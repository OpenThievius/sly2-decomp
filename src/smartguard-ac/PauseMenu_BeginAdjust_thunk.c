/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pausemenu.h"

void func_001AF6A0(PAUSEMENU *pmenu);
extern PAUSEMENU B_003D9ED0;

void PauseMenu_BeginAdjust_thunk(void) {
    func_001AF6A0(&B_003D9ED0);
}

/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pausemenu.h"

void func_001AF490(PAUSEMENU *pmenu);
extern PAUSEMENU B_003D9ED0;

void PauseMenu_PopPage_thunk(void) {
    func_001AF490(&B_003D9ED0);
}

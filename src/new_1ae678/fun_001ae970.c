/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pausemenu.h"

void PauseMenu_Close(PAUSEMENU *pmenu);
void PauseMenu_SetState(PAUSEMENU *pmenu, s32 state);

void func_001AE970(PAUSEMENU *pmenu) {
    PauseMenu_Close(pmenu);
    PauseMenu_SetState(pmenu, 0);
    pmenu->pblot = 0;
}

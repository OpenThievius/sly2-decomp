/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pausemenu.h"

void PauseMenu_Close(PAUSEMENU *pmenu);
extern PAUSEMENU B_003D9ED0;

void PauseMenu_Close_thunk(void) {
    PauseMenu_Close(&B_003D9ED0);
}

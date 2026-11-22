/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pausemenu.h"

void PauseMenu_SetState(PAUSEMENU *pmenu, s32 state);

void PauseMenu_Close(PAUSEMENU *pmenu) {
    if (pmenu->state == 7) {
        if (pmenu->depth >= 2) {
            pmenu->depth = 1;
        }
        PauseMenu_SetState(pmenu, 8);
    }
}

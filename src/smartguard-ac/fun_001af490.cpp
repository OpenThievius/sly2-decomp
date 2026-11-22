// SPDX-License-Identifier: GPL-3.0-or-later
#include "pausemenu.h"
extern "C" {
void PauseMenu_SetState(PAUSEMENU *pmenu, int state);

void func_001AF490(PAUSEMENU *pmenu) {
    if (pmenu->state == 7) {
        PauseMenu_SetState(pmenu, 3);
        pmenu->depthNext = pmenu->depth - 1;
    }
}

}

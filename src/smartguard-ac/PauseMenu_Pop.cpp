// SPDX-License-Identifier: GPL-3.0-or-later
#include "pausemenu.h"
extern "C" {
void PauseMenu_SetState(PAUSEMENU *pmenu, int state);
int func_001B0108(PAUSEMENU *pmenu);

void PauseMenu_Pop(PAUSEMENU *pmenu) {
    int depthNew;

    if (pmenu->state == 7) {
        PauseMenu_SetState(pmenu, 2);
        if (func_001B0108(pmenu) != 0) {
            depthNew = pmenu->depth - 1;
            pmenu->depth = depthNew;
            pmenu->depthNext = depthNew;
        }
    }
}

}

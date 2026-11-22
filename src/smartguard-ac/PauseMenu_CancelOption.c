/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pausemenu.h"

void ApplyOptionsFromSave(void *psave);
void PauseMenu_SetState(PAUSEMENU *pmenu, s32 state);
extern char B_003D4A60[];

/* pitem: PauseMenu_Update passes the item, retail ignores it */
void PauseMenu_CancelOption(PAUSEMENU *pmenu, PAUSEITEM *pitem) {
    ApplyOptionsFromSave(B_003D4A60);
    PauseMenu_SetState(pmenu, 9);
}

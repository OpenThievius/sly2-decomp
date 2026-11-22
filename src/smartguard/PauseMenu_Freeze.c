/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pausemenu.h"

void func_00187E78(void *pjoy);
void func_001D98A8(void);

void PauseMenu_Freeze(PAUSEMENU *pmenu, s32 fResetNav) {
    func_001D98A8();
    if (fResetNav != 0) {
        func_00187E78(pmenu->pjoy);
    }
}

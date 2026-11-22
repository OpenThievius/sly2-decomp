/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "memcardmenu.h"

void MemcardMenu_SetState(MEMCARDMENU *pmenu, s32 state);
void Menu_PostLoad();

void MemcardMenu_PostLoad(MEMCARDMENU *pmenu) {
    s32 state;
    MENUOBJECT *pobject;

    Menu_PostLoad();
    pobject = pmenu->pobject;
    if (pobject != 0) {
        pobject->field_0xB0 = 1;
        state = pmenu->state;
        if (state != -1) {
            MemcardMenu_SetState(pmenu, state);
        }
    }
}

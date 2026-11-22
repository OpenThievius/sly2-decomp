// SPDX-License-Identifier: GPL-3.0-or-later
#include "memcardmenu.h"
extern "C" {
MEMCARDMENU *Menu_Construct(MEMCARDMENU *);
void Menu_ResetState(MEMCARDMENU *);
extern int D_002D3750;

MEMCARDMENU *MemcardMenu_Construct(MEMCARDMENU *pmenu) {
    Menu_Construct(pmenu);
    pmenu->pvtbl = &D_002D3750;
    pmenu->oid = 0x52C;
    pmenu->state = -1;
    Menu_ResetState(pmenu);
    return pmenu;
}

}

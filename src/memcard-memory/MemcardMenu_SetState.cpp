#include "menu.h"
#include "blot.h"
/* MEMCARDMENU (memcardmenu.h) as a MENU: its state word follows the base class' 0x40 bytes (MemcardMenu_SetState, MemcardMenu_ClearState) */
struct MEMCARDMENUSTATE : MENU {
    /* 0x40 */ s32 state;
};
extern "C" {
void MemcardMenu_SetState(MEMCARDMENUSTATE *self, int state) {
    self->state = state;
    if (self->pblot) {
        self->Slot10();
        self->pblot->Select(-1);
    }
}
}

#include "types.h"
#include "menu.h"

void *PloFindSwObject_thunk(s32 *, s32, s32, s32);
extern s32 B_003DD490;

void Menu_PostLoad(MENUVIEW *menu) {
    menu->pblot = PloFindSwObject_thunk(&B_003DD490, 5, menu->oid, 0);
}

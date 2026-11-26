#include "types.h"
#include "menu.h"

extern "C" {
struct MenuVtable;

void Menu_ResetState(MENUVIEW *);
extern struct MenuVtable D_002D85E8;

MENUVIEW *Menu_Construct(MENUVIEW *menu) {
    menu->pframe = 0;
    menu->psidebag = 0;
    menu->vtable = &D_002D85E8;
    menu->oid = -1;
    Menu_ResetState(menu);
    return menu;
}

}

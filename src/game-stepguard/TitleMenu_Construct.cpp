#include "types.h"
#include "menu.h"

extern "C" {
struct MenuVtable;

MENUVIEW *Menu_Construct(MENUVIEW *);
void Menu_ResetState(MENUVIEW *);
extern struct MenuVtable D_002D8368;

MENUVIEW *TitleMenu_Construct(MENUVIEW *menu) {
    Menu_Construct(menu);
    menu->oid = 0x5D2;
    menu->vtable = &D_002D8368;
    Menu_ResetState(menu);
    return menu;
}

}

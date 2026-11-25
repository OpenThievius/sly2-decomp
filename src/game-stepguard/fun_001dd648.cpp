#include "types.h"
#include "menu.h"

extern "C" {
struct MenuVtable;

MENUVIEW *Menu_Construct(MENUVIEW *);
void Menu_ResetState(MENUVIEW *);
extern struct MenuVtable D_002D83E8;

MENUVIEW *func_001DD648(MENUVIEW *menu) {
    Menu_Construct(menu);
    menu->oid = 0x52D;
    menu->vtable = &D_002D83E8;
    Menu_ResetState(menu);
    return menu;
}

}

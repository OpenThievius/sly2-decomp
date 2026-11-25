#include "types.h"
#include "menu.h"

extern "C" {
struct MenuVtable;

MENUVIEW *Menu_Construct(MENUVIEW *);
void ShopMenu_InitPage(MENUVIEW *);
extern struct MenuVtable D_002D84E8;

MENUVIEW *ShopMenu_Construct(MENUVIEW *menu) {
    Menu_Construct(menu);
    menu->oid = 0x378;
    menu->vtable = &D_002D84E8;
    ShopMenu_InitPage(menu);
    return menu;
}

}

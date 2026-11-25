#include "types.h"
#include "menu.h"

struct MenuVtable;

MENUVIEW *Menu_Construct(MENUVIEW *);
void GadgetMenu_InitPage(MENUVIEW *);
extern struct MenuVtable D_002D8568;

MENUVIEW *GadgetMenu_Construct(MENUVIEW *menu) {
    Menu_Construct(menu);
    menu->vtable = &D_002D8568;
    GadgetMenu_InitPage(menu);
    return menu;
}

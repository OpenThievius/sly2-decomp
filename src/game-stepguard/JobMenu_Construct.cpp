#include "types.h"
#include "menu.h"

extern "C" {
struct MenuVtable;

MENUVIEW *Menu_Construct(MENUVIEW *);
void JobMenu_InitPage(MENUVIEW *);
extern struct MenuVtable D_002D8468;

MENUVIEW *JobMenu_Construct(MENUVIEW *menu) {
    Menu_Construct(menu);
    menu->oid = 0x4E0;
    menu->vtable = &D_002D8468;
    JobMenu_InitPage(menu);
    return menu;
}

}

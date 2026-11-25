#include "menu.h"
#include "blot.h"
extern "C" void Menu_PostLoad(MENU *);
extern "C" void func_001DD690(MENU *menu)
{
    Menu_PostLoad(menu);
    if (menu->pblot)
        menu->pblot->fSlowsClock = 1;
}

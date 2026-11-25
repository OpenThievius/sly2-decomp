#include "jobmenu.h"
extern "C" void Menu_ClearDialog(JOBMENU *, int);
extern "C" void JobMenu_Select(JOBMENU *menu, int index)
{
    int selected;
    if (menu->cent == 0) {
        selected = -1;
    } else {
        int last = menu->cent - 1;
        selected = 0;
        if (index >= 0)
            selected = (last >= index) ? index : last;
    }
    menu->isel = selected;
    Menu_ClearDialog(menu, index);
}

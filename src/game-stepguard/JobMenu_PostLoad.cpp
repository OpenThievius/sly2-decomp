#include "jobmenu.h"
#include "blot.h"
extern "C" void Menu_PostLoad(JOBMENU *);
extern "C" void JobMenu_PostLoad(JOBMENU *menu)
{
    Menu_PostLoad(menu);
    BLOT *pblot = menu->pblot;
    if (pblot)
        pblot->fSlowsClock = 1;
}

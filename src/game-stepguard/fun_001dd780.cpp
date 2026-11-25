#include "menu.h"
#include "blot.h"
extern "C" bool func_001DD780(MENU *menu)
{
    BLOT *pblot = menu->pblot;
    if (pblot == 0) return false;
    if (pblot->blots != 2) return false;
    return pblot->field_0x64 == 2;
}

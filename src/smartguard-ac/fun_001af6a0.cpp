#include "pausemenu.h"
extern "C" void PauseMenu_SetState(PAUSEMENU *menu, int state);
extern "C" void func_001AF6A0(PAUSEMENU *menu)
{
    if (menu->state == 7)
        PauseMenu_SetState(menu, 0xB);
}

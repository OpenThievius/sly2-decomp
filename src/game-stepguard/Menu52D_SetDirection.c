#include "types.h"
#include "menu.h"
#include "clock.h"

void Menu52D_SetDirection(MENUVIEW *menu, s32 direction) {
    if (direction != menu->direction) {
        menu->direction = direction;
        menu->tDirection = g_2dded0.tReal;
    }
}

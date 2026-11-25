// SPDX-License-Identifier: GPL-3.0-or-later
#include "jobmenu.h"
#include "clock.h"
struct EMITTER1DD558;
extern "C" {
void JobMenu_SetPage(JOBMENU *, int);
void JobMenu_Select(JOBMENU *, int);
EMITTER1DD558 *NewEmitter(int);
void SetEmitterUnpositioned(EMITTER1DD558 *, int);
void JobMenu_SetDirection(JOBMENU *menu, int direction)
{
    if (direction == menu->direction)
        return;
    menu->direction = direction;
    menu->tDirection = g_2dded0.tReal;
    switch (direction) {
    case 0:
        if (menu->cent != 0)
            JobMenu_SetPage(menu, 1);
        break;
    case 4:
        JobMenu_SetPage(menu, 0);
        break;
    case 1:
    case 2:
    case 3: {
        int index = menu->isel;
        if (index > 0) {
            JobMenu_Select(menu, index - 1);
            SetEmitterUnpositioned(NewEmitter(0x35), 0);
        }
        break;
    }
    case 5:
    case 6:
    case 7: {
        int index = menu->isel;
        if (index < menu->cent - 1) {
            JobMenu_Select(menu, index + 1);
            SetEmitterUnpositioned(NewEmitter(0x35), 0);
        }
        break;
    }
    }
}
}

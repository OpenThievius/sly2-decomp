// SPDX-License-Identifier: GPL-3.0-or-later
#include "shopmenu.h"
#include "clock.h"
struct EMITTER1DC4B0;
extern "C" {
void ShopMenu_SetPage(SHOPMENU *, int);
void ShopMenu_Select(SHOPMENU *, int);
EMITTER1DC4B0 *NewEmitter(int);
void SetEmitterUnpositioned(EMITTER1DC4B0 *, int);
void ShopMenu_SetDirection(SHOPMENU *menu, int direction)
{
    if (direction == menu->direction)
        return;
    menu->direction = direction;
    menu->tDirection = g_2dded0.tReal;
    switch (direction) {
    case 0:
        ShopMenu_SetPage(menu, 1);
        break;
    case 4:
        ShopMenu_SetPage(menu, 0);
        break;
    case 1:
    case 2:
    case 3: {
        int index = menu->isel;
        if (index > 0) {
            ShopMenu_Select(menu, index - 1);
            SetEmitterUnpositioned(NewEmitter(0x35), 0);
        } else {
            SetEmitterUnpositioned(NewEmitter(0x36), 0);
        }
        break;
    }
    case 5:
    case 6:
    case 7: {
        int index = menu->isel;
        if (index < menu->count - 1) {
            ShopMenu_Select(menu, index + 1);
            SetEmitterUnpositioned(NewEmitter(0x35), 0);
        } else {
            SetEmitterUnpositioned(NewEmitter(0x36), 0);
        }
        break;
    }
    }
}
}

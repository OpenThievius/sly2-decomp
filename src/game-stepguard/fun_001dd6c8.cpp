#include "menu.h"
#include "blot.h"
extern "C" {
void func_001DD6C8(MENU *menu) {
    if (menu->pblot) {
        menu->Slot10();
        menu->pblot->Select(-1);
    }
}
}

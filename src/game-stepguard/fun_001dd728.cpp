#include "menu.h"
#include "blot.h"
extern "C" {
void func_001DD728(MENU *menu) {
    if (menu->pblot) {
        menu->Slot11();
        menu->pblot->Hide();
    }
}
}

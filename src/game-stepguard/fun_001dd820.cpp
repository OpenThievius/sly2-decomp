#include "menu.h"
#include "blot.h"
extern "C" {
void RumbleUnknown1__Fv();
void func_001DD820(MENU *menu) {
    if (menu->pblot) {
        menu->Slot10();
        menu->pblot->Select(-1);
        RumbleUnknown1__Fv();
    }
}
}

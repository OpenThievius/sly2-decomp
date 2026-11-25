#include "menu.h"
#include "blot.h"

extern "C" {
void func_001DD888(MENU *menu) {
    if (menu->pblot != 0) {
        menu->Slot11();
        menu->pblot->Hide();
    }
}

}

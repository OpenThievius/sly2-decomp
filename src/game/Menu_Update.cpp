#include "types.h"
#include "menu.h"
#include "clock.h"

extern "C" {
void Menu_SetDialog(MENU *, s32, s32);
void func_001D9870(void);

void Menu_Update(MENU *menu) {
    func_001D9870();
    if (menu->tDialogEnd <= g_2dded0.tReal) {
        Menu_SetDialog(menu, -1, -1);
    }
}

}

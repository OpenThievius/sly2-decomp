#include "menu.h"
extern "C" void Menu_ResetState(MENU *);
void Menu_Reset(MENU *self) {
    self->pblot = 0;
    Menu_ResetState(self);
}

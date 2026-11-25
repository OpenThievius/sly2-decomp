#include "gadgetmenu.h"
extern "C" void func_00213928(int, int);
extern "C" void func_00213B00(int, int);

void GadgetMenu_SelectGadget(GADGETMENU *menu, int gadget)
{
    menu->gadget = gadget;
    for (int index = 0; index < menu->cgme; index++) {
        GADGETMENUENTRY *gme = &menu->agme[index];
        int label;
        if (gme->id == gadget) {
            label = gme->labels[2];
        } else if ((gme->flags & 4) != 0) {
            label = gme->labels[1];
        } else {
            label = ((gme->flags & 2) != 0) ? gme->labels[0] : -1;
        }
        if (label == gme->labelCur)
            continue;
        if (menu->pblot != 0 && gme->labelCur != -1)
            func_00213928(menu->pblot, gme->labelCur);
        gme->labelCur = label;
        if (menu->pblot != 0 && label != -1)
            func_00213B00(menu->pblot, label);
    }
}

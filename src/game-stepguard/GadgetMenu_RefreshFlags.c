#include "gadgetmenu.h"

s32 FGadgetAcquired(s32);
s32 FGadgetOnSale(s32);

void GadgetMenu_RefreshFlags(GADGETMENU *menu) {
    s32 index;
    GADGETMENUENTRY *entry;

    index = 0;
    if (menu->cgme > 0) {
        do {
            entry = &menu->agme[index];
            index += 1;
            entry->flags = (entry->flags & ~2) | ((FGadgetOnSale(entry->id) & 1) * 2);
            entry->flags = (entry->flags & ~4) | ((FGadgetAcquired(entry->id) & 1) * 4);
        } while (index < menu->cgme);
    }
}

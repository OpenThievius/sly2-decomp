#include "gadgetmenu.h"
extern "C" GADGETMENUENTRY *GadgetMenu_PgmeFind(GADGETMENU *menu, int id)
{
    int count = menu->cgme;
    if (count > 0) {
        int index = 0;
        GADGETMENUENTRY *entry = menu->agme;
        do {
            index++;
            if (entry->id == id)
                return entry;
            entry++;
        } while (index < count);
    }
    return 0;
}

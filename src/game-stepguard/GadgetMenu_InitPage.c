#include "gadgetmenu.h"

struct FloatGlobal {
    f32 value;
};

extern struct FloatGlobal g_2ddf0c;

void GadgetMenu_InitPage(GADGETMENU *menu) {
    menu->page = -1;
    menu->clock = g_2ddf0c.value;
}

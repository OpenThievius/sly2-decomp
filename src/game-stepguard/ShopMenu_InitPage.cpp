#include "clock.h"
#include "shopmenu.h"
extern "C" {
void ShopMenu_InitPage(SHOPMENU *page) {
    u32 var_a2;
    s32 *var_a1;

    page->mode = -1;
    var_a1 = &page->arow[0].label;
    var_a2 = 0;
    page->tPage = g_2dded0.tReal;
    page->labelDialog = -1;
    page->labelUp = -1;
    page->labelDown = -1;
    do {
        var_a1[-1] = -1;
        var_a2 += 1;
        var_a1[0] = -1;
        var_a1 += 2;
    } while (var_a2 < 0x40U);
}
}

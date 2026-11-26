#include "clock.h"
/* the shop menu's page, reset to -1 (no recovered name) */
struct SHOPMENUPAGE {
    u8 unknown_0x0[0x40];
    /* 0x40 */ s32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    u8 unknown_0x48[0x4];
    /* 0x4C */ s32 aslot[0x80];  /* 0x40 pairs, ShopMenu_InitPage writes -1 to both */
    u8 unknown_0x24C[0x10];
    /* 0x25C */ s32 field_0x25C;
    /* 0x260 */ s32 field_0x260;
    /* 0x264 */ s32 field_0x264;
};
extern "C" {
void ShopMenu_InitPage(SHOPMENUPAGE *page) {
    u32 var_a2;
    s32 *var_a1;

    page->field_0x40 = -1;
    var_a1 = &page->aslot[1];
    var_a2 = 0;
    page->field_0x44 = g_2dded0.tReal;
    page->field_0x25C = -1;
    page->field_0x260 = -1;
    page->field_0x264 = -1;
    do {
        var_a1[-1] = -1;
        var_a2 += 1;
        var_a1[0] = -1;
        var_a1 += 2;
    } while (var_a2 < 0x40U);
}
}

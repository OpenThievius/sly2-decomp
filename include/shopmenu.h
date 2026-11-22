/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SHOPMENU, the shop menu object (retail's B_003DA150, constructed by ShopMenu_Construct on top of Menu_Construct), and
   GADGETDEF, one 0x20-byte row of the gadget table D_002BCD00. Fields from the matched shop functions of src/game-stepguard/
   (ShopMenu_BuildList, _InitPage, _Update, _Select, _IrowEnd, _UpdateBlot, GetShopRowName, GetShopRowPrice). C and C++. */
#ifndef SLY2_SHOPMENU_H
#define SLY2_SHOPMENU_H
#include "types.h"

/* a row of the gadget table (D_002BCD00, 0x2B rows) */
struct GADGETDEF {
    u8 unknown_0x0[8];
    /* 0x08 */ s32 price;       /* ShopMenu_Update, GetShopRowPrice */
    u8 unknown_0xC[4];
    /* 0x10 */ s32 episodeMin;  /* FGadgetOnSale: -1 never on sale, else on sale once NEpisodeBest() reaches it */
    /* 0x14 */ s32 sidName;     /* GetShopRowName: the string id of the gadget's name, -1 for none */
    u8 unknown_0x18[8];
};

/* a visible row: BuildList stores the gadget (mode 0) or slot (mode 1) index, InitPage clears both words to -1 */
struct SHOPROW {
    /* 0x0 */ s32 id;
    /* 0x4 */ s32 field_0x4;
};

struct SHOPMENU {
    u8 unknown_0x0[0xC];
    /* 0x0C */ void *vtable;
    /* 0x10 */ void *dev;            /* ShopMenu_Update: the pad FJoyButtonPressed reads */
    u8 unknown_0x14[0x1C];
    /* 0x30 */ s32 dialog;           /* ShopMenu_Update: nonzero while a dialog is up */
    u8 unknown_0x34[0xC];
    /* 0x40 */ s32 mode;             /* 0 gadgets, 1 loot, -1 none: InitPage sets -1 */
    /* 0x44 */ f32 field_0x44;       /* InitPage copies g_2ddf0c into it */
    /* 0x48 */ s32 count;            /* BuildList: the number of rows in arow */
    /* 0x4C */ struct SHOPROW arow[0x40]; /* BuildList takes up to 0x41 rows, as retail's bound reads (the last one lands on isel) */
    /* 0x24C */ s32 isel;            /* BuildList reselects it; ShopMenu_Select stores it */
    /* 0x250 */ s32 ifirst;          /* the first visible row: GetShopRowName, GetShopRowPrice */
    /* 0x254 */ s32 idGadget;        /* the selected row's id in mode 0: ShopMenu_Update buys it */
    /* 0x258 */ s32 idLoot;          /* the selected row's id in mode 1: ShopMenu_Update sells it */
    /* 0x25C */ s32 field_0x25C;     /* InitPage clears them to -1 */
    /* 0x260 */ s32 field_0x260;
    /* 0x264 */ s32 field_0x264;
};
#endif

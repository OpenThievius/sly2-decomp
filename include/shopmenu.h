/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SHOPMENU, the shop menu object (retail's B_003DA150, constructed by ShopMenu_Construct on top of Menu_Construct): a MENU, and
   GADGETDEF, one 0x20-byte row of the gadget table D_002BCD00, LOOTROW, one 12-byte row of the loot table D_002C3288. Fields from
   the matched shop functions of src/game-stepguard/ (ShopMenu_BuildList, _InitPage, _Update, _Select, _IrowEnd, _UpdateBlot,
   _SetPage, _SetDirection, GetShopRowName, GetShopRowPrice, func_001DCAB0; GetLootRowName, GetLootRowPrice, GetGadgetMenuText for the tables). C++. */
#ifndef SLY2_SHOPMENU_H
#define SLY2_SHOPMENU_H
#include "types.h"
#include "menu.h"

/* a row of the gadget table (D_002BCD00, 0x2B rows) */
struct GADGETDEF {
    u8 unknown_0x0[4];
    /* 0x04 */ s32 type;        /* ShopMenu_UpdateBlot: 7, 8 and 9 pick the row's label (the table was read as D_002BCD04) */
    /* 0x08 */ s32 price;       /* ShopMenu_Update, GetShopRowPrice */
    u8 unknown_0xC[4];
    /* 0x10 */ s32 episodeMin;  /* FGadgetOnSale: -1 never on sale, else on sale once NEpisodeBest() reaches it */
    /* 0x14 */ s32 sidName;     /* GetShopRowName, GetGadgetMenuText: the string id of the gadget's name, -1 for none */
    /* 0x18 */ s32 sidDesc;     /* func_001DCAB0, GetGadgetMenuText: the string id of its description, -1 for none */
    /* 0x1C */ s32 sidHint;     /* GetGadgetMenuText: the string id of its button hint, a format with three %s for the slot's name */
};

/* a row of the loot table D_002C3288 (0xC bytes, 0x40 rows, indexed by a loot id): the sale price and the string id of the name */
struct LOOTROW {
    /* 0x0 */ s32 price;         /* GetLootRowPrice; ShopMenu_Update adds it to the coins on a sale; func_001DCAB0 shows it */
    /* 0x4 */ s32 sidName;       /* GetLootRowName: -1 for none */
    u8 unknown_0x8[4];
};

/* a visible row: BuildList stores the gadget (mode 0) or slot (mode 1) index, InitPage clears both words to -1 */
struct SHOPROW {
    /* 0x0 */ s32 id;
    /* 0x4 */ s32 label;        /* ShopMenu_UpdateBlot: the row's label slot */
};

struct SHOPMENU : MENU {
    /* 0x40 */ s32 mode;             /* 0 gadgets, 1 loot, -1 none (the page): InitPage sets -1; SetPage, SetDirection, Update, UpdateBlot */
    /* 0x44 */ f32 tPage;            /* the real time the page changed: InitPage copies g_2ddf0c into it, SetPage */
    /* 0x48 */ s32 count;            /* BuildList: the number of rows in arow */
    /* 0x4C */ struct SHOPROW arow[0x40]; /* BuildList takes up to 0x41 rows, as retail's bound reads (the last one lands on isel) */
    /* 0x24C */ s32 isel;            /* BuildList reselects it; ShopMenu_Select stores it */
    /* 0x250 */ s32 ifirst;          /* the first visible row: GetShopRowName, GetShopRowPrice, ShopMenu_UpdateBlot (itop) */
    /* 0x254 */ s32 idGadget;        /* the selected row's id in mode 0: ShopMenu_Update buys it, func_001DCAB0 */
    /* 0x258 */ s32 idLoot;          /* the selected row's id in mode 1: ShopMenu_Update sells it, func_001DCAB0 */
    /* 0x25C */ s32 labelDialog;     /* InitPage clears them to -1; ShopMenu_UpdateBlot switches the dialog's label here */
    /* 0x260 */ s32 labelUp;         /* the up arrow's label */
    /* 0x264 */ s32 labelDown;       /* the down arrow's label */
};
#if defined(__mips__)
SLY2_SIZE_CHECK(SHOPMENU, 0x268);
SLY2_OFFSET_CHECK(SHOPMENU, isel, 0x24C);
SLY2_OFFSET_CHECK(SHOPMENU, labelDown, 0x264);
#endif
#endif

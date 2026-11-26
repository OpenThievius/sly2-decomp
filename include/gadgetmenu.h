/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GADGETMENU, the gadget menu object (retail's B_003DA0F0: a Menu, vtable pointer at 0xC, built by Menu_Construct), and
   GADGETMENUENTRY: one row of the gadget menu's pages (D_002C2DE8, D_002C3028, D_002C3148), 0x20 bytes, as GadgetMenu_SetPage and
   GadgetMenu_SelectGadget read them (the labels the blot plays at 4 to 0x10, the two floats SetPage adds at 0x14 and 0x18, flags at
   0x1C: bit 1 on sale, bit 2 acquired, bit 4) and the splice-gc-wipe code steps through them (the id at 0). Fields from the matched
   sources of src/game-stepguard/ (GadgetMenu_SetPage, _SelectGadget, _Update, _InitPage, _RefreshFlags, _PgmeFind, _DrawSlotLabels,
   GetGadgetMenuText). The pages are defined in src/data. C and C++. */
#ifndef SLY2_GADGETMENU_H
#define SLY2_GADGETMENU_H
#include "types.h"

typedef struct GADGETMENUENTRY {
    /* 0x00 */ s32 id;           /* the gadget the row stands for (GadgetMenu_PgmeFind compares it) */
    /* 0x04 */ s32 labels[3];    /* the blot labels of a row: [0] on sale, [1] acquired, [2] selected (GadgetMenu_SelectGadget) */
    /* 0x10 */ s32 labelCur;     /* the label it shows now, -1 for none: SelectGadget changes it, SetPage resets it (the data names it link) */
    /* 0x14 */ f32 low;          /* GadgetMenu_DrawSlotLabels draws a slot's text at (low, high) */
    /* 0x18 */ f32 high;
    /* 0x1C */ s32 flags;        /* GadgetMenu_RefreshFlags: bit 1 on sale, bit 2 acquired, bit 0 (tested by GetGadgetMenuText and GadgetMenu_Update) */
} GADGETMENUENTRY;

typedef struct GADGETMENU {
    u8 unknown_0x0[0xC];
    /* 0x0C */ void *vtable;     /* GadgetMenu_SetPage calls slots 10, 11, 49 and 50 by hand */
    /* 0x10 */ s32 pjoy;         /* GadgetMenu_Update: the pad FJoyButtonPressed reads */
    u8 unknown_0x14[0xC];
    /* 0x20 */ s32 idDialog;     /* GadgetMenu_SetPage: the id of the page's dialog object (0x375 to 0x377) */
    /* 0x24 */ s32 pblot;        /* the page's blot (SetPage finds it by idDialog); FDrawBlotMovie, GadgetMenu_Update, GadgetMenu_SelectGadget */
    u8 unknown_0x28[8];
    /* 0x30 */ s32 dialog;       /* GadgetMenu_Update, GetGadgetMenuText: -1 when no message dialog is up */
    u8 unknown_0x34[4];
    /* 0x38 */ s32 msgDialog;    /* GetGadgetMenuText: the string id of the dialog's message */
    u8 unknown_0x3C[4];
    /* 0x40 */ s32 page;         /* GadgetMenu_SetPage: -1 closed, else 0 to 2 */
    /* 0x44 */ f32 clock;        /* GadgetMenu_SetPage stores the clock's rate */
    /* 0x48 */ s32 gadget;       /* the selected gadget, -1 for none: GadgetMenu_SelectGadget */
    /* 0x4C */ s32 cgme;         /* the number of rows of agme */
    /* 0x50 */ GADGETMENUENTRY *agme;
} GADGETMENU;

#ifdef __cplusplus
#include "menu.h"
/* the same object as a MENU subclass (C++ only): GadgetMenu_SetPage calls the menu's slots 10 and 11 as virtuals, the blot's through BLOT */
struct GADGETMENUOBJ : MENU {
    /* 0x40 */ s32 page;
    /* 0x44 */ f32 clock;
    /* 0x48 */ s32 gadget;
    /* 0x4C */ s32 cgme;
    /* 0x50 */ GADGETMENUENTRY *agme;
};
#endif
#endif

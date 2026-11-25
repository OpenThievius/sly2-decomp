/* SPDX-License-Identifier: GPL-3.0-or-later */
/* MENU, the menus' base class (Menu_Construct, Menu_PostLoad, Menu_ResetState, Menu_SetDialog, Menu_Update; the job, shop, title,
   gadget, memory card and pause-menu-launching menus derive from it). A BASIC (vtable at 0xC, 0x10 bytes) with the controller, the
   object id of its blot and the blot, the direction the stick last pressed and the dialog. Its virtuals start at slot 7 (the
   callers show slots 10, 11 and 14). Names are ours, from what the readers do. MENUVIEW is the flat view of the same 0x40 bytes
   for C sources and for the constructors, which store the class's vtable by hand (as BLOTVIEW does for BLOT). */
#ifndef SLY2_MENU_H
#define SLY2_MENU_H
#include "types.h"
#ifdef __cplusplus
#include "lo.h"
#endif

struct JOY;
struct BLOT;

typedef struct MENUVIEW {
    u8 unknown_0x0[0xC];
    /* 0x0C */ void *vtable;      /* the constructors store the class's table (Shop/Job/Title/Gadget/Menu52D_Construct) */
    /* 0x10 */ struct JOY *pjoy;  /* TitleMenu_Update, JobMenu_Update, ShopMenu_Update, MemcardMenu_Update read the controller here */
    u8 unknown_0x14[0xC];
    /* 0x20 */ s32 oid;           /* Menu_Construct sets -1, the constructors their own id; Menu_PostLoad finds the blot by it */
    /* 0x24 */ struct BLOT *pblot; /* Menu_PostLoad (PloFindSwObject kind 5), Menu_Reset clears it, every menu's Update tests it */
    /* 0x28 */ s32 direction;     /* Menu_ResetState sets -1; the *_SetDirection functions */
    /* 0x2C */ f32 tDirection;    /* the real time direction last changed: the *_SetDirection functions, Menu_ResetState */
    /* 0x30 */ s32 dialogKind;    /* Menu_SetDialog: -1 none; ShopMenu_Update */
    /* 0x34 */ f32 tDialogEnd;    /* Menu_SetDialog, Menu_Update */
    /* 0x38 */ s32 dialogArg;     /* Menu_SetDialog; func_001DCAB0 reads it as a string id */
    u8 unknown_0x3C[0x4];
} MENUVIEW;

#ifdef __cplusplus
struct MENU : BASIC {
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Slot10();             /* 10: the menu's Open? JobMenu_SetPage and ShopMenu_SetPage call it when the first page opens, func_001DD6C8 and func_001DD820 before the blot's select */
    virtual void Slot11();             /* 11: the matching close: SetPage's page -1, func_001DD728, func_001DD888 */
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14(s32 selector); /* 14: SetPage ends with it, passing -1 */
    virtual void Slot15();
    virtual void Slot16();
    /* 0x10 */ struct JOY *pjoy;
    u8 unknown_0x14[0xC];
    /* 0x20 */ s32 oid;
    /* 0x24 */ struct BLOT *pblot;
    /* 0x28 */ s32 direction;
    /* 0x2C */ f32 tDirection;
    /* 0x30 */ s32 dialogKind;
    /* 0x34 */ f32 tDialogEnd;
    /* 0x38 */ s32 dialogArg;
    u8 unknown_0x3C[0x4];
};
#if defined(__mips__)
SLY2_SIZE_CHECK(MENU, 0x40);
SLY2_OFFSET_CHECK(MENU, pjoy, 0x10);
SLY2_OFFSET_CHECK(MENU, pblot, 0x24);
SLY2_OFFSET_CHECK(MENU, dialogArg, 0x38);
#endif
#endif
#endif

/* SPDX-License-Identifier: GPL-3.0-or-later */
/* MEMCARDMENU, the memory card menu (retail's B_002E6550, 0x90 bytes before the SAVE at 0x2E65E0): the menu base class' fields
   (Menu_Construct, Menu_PostLoad, Menu_ResetState, 0x0 to 0x20 and 0x24 to 0x2C) and the card menu's own state words. Names are
   ours, from the MemcardMenu_* functions: state is MemcardMenu_SetState's (MemcardMenu_KindOfState sorts it), phase and its time
   are func_001ACC38's, dir and its time MemcardMenu_SetDir's. Several sources used to declare their own prefix of it (a
   `struct MENU { char pad[0x44]; int phase; }`). C and C++. */
#ifndef SLY2_MEMCARDMENU_H
#define SLY2_MEMCARDMENU_H
#include "types.h"

struct JOY;

/* The object a menu finds in the world by its oid (Menu_PostLoad: PloFindSwObject kind 5): an LO of the menu's sprites. Only the
   words the card menu reads. */
typedef struct MENUOBJECT {
    u8 unknown_0x0[0x58];
    /* 0x58 */ s32 field_0x58; /* MemcardMenu_Update: the menu acts only when it is 2 */
    /* 0x5C */ f32 field_0x5C; /* MemcardMenu_Update: a time, the menu waits 0.1 s after it */
    u8 unknown_0x60[0x4];
    /* 0x64 */ s32 field_0x64; /* MemcardMenu_Update: must be 2 as well */
    u8 unknown_0x68[0x48];
    /* 0xB0 */ s32 field_0xB0; /* MemcardMenu_PostLoad sets it to 1 */
} MENUOBJECT;

typedef struct MEMCARDMENU {
    u8 unknown_0x0[0xC];
    /* 0x0C */ void *pvtbl;    /* MemcardMenu_Construct stores retail's vtable (D_002D3750) over the base class' */
    /* 0x10 */ struct JOY *pjoy; /* MemcardMenu_Update: the controller whose buttons close or confirm the menu */
    u8 unknown_0x14[0xC];
    /* 0x20 */ s32 oid;        /* Menu_Construct sets -1, MemcardMenu_Construct 0x52C; Menu_PostLoad finds the object by it */
    /* 0x24 */ MENUOBJECT *pobject; /* Menu_PostLoad, MemcardMenu_PostLoad, MemcardMenu_Update */
    /* 0x28 */ s32 dir;        /* Menu_ResetState sets -1; MemcardMenu_SetDir */
    /* 0x2C */ f32 tDir;       /* the time dir last changed: MemcardMenu_SetDir */
    u8 unknown_0x30[0x10];
    /* 0x40 */ s32 state;      /* MemcardMenu_SetState's, -1 when none: MemcardMenu_Construct, MemcardMenu_PostLoad, MemcardMenu_KindOfState */
    /* 0x44 */ s32 phase;      /* func_001ACC38 (SetSaveState and UpdateSave read it); MemcardMenu_Update */
    /* 0x48 */ f32 tPhase;     /* the time phase last changed: func_001ACC38 */
    /* 0x4C */ s32 mode;       /* MemcardMenu_Update's follow-up after a save (1 restart the boot queue, 2 close the pause menu, 3) */
} MEMCARDMENU;

#endif

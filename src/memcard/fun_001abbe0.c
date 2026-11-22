/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

#include "memcard.h"

/* The memory card manager object: lives inside SAVE at 0xFD5C. */
typedef struct B8 { char b[8]; } B8;




typedef struct MENU {
    /* 0x00 */ u8 unknown_0x0[0x44];
    /* 0x44 */ s32 phase;
} MENU;

void BusyMenu_Hide(void *);                         /* extern */
s32 CheckCardStatus(SAVE *);                        /* extern */
void MemcardMenu_SetState(MENU *, s32);             /* extern */
s32 WriteSaveSlot(SAVE *, SLOT *);                  /* extern */
void func_001ACC38(MENU *, s32);                    /* extern */
extern MENU B_002E6550;
extern u8 B_002E65A0[];

s32 func_001ABBE0(SAVE *save) {
    s32 error;

    error = CheckCardStatus(save);
    if ((error != 0) || (error = WriteSaveSlot(save, save->pslotCur), (error != 0))) {
        func_001ACC38(&B_002E6550, 3);
        MemcardMenu_SetState(&B_002E6550, 0x23);
        BusyMenu_Hide(B_002E65A0);
    }
    return error;
}

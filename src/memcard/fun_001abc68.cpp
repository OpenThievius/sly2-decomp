// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

#include "memcard.h"

/* The memory card manager object: lives inside SAVE at 0xFD5C. */
typedef struct B8 { char b[8]; } B8;




typedef struct MENU {
    /* 0x00 */ u8 unknown_0x0[0x44];
    /* 0x44 */ s32 phase;
} MENU;

s32 CheckCardStatus(SAVE *);
s32 CreateSaveDirectory(SAVE *);
s32 InitAndWriteSaveSlot(SAVE *, SLOT *);
void func_001ACC38(MENU *, s32);
extern MENU B_002E6550;

s32 func_001ABC68(SAVE *save)
{
    s32 result = CheckCardStatus(save);
    if (result == 0) {
        result = CreateSaveDirectory(save);
        if (result == 0) {
            result = InitAndWriteSaveSlot(save, save->pslotInit);
        }
    }
    if (result != 0) {
        func_001ACC38(&B_002E6550, 3);
    }
    return result;
}

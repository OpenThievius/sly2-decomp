/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

#include "memcard.h"

/* The memory card manager object: lives inside SAVE at 0xFD5C. */
typedef struct B8 { char b[8]; } B8;




typedef struct MENU {
    /* 0x00 */ u8 unknown_0x0[0x44];
    /* 0x44 */ s32 phase;
} MENU;

s32 McSync(void *, s32, s32, s32 *);                /* extern */
void func_001ACC38(MENU *, s32);                    /* extern */
s32 sceMcFormat(s32, s32);                          /* extern */
extern MENU B_002E6550;

s32 FormatMemcard(SAVE *save) {
    s32 error;

    error = McSync(&save->mc, sceMcFormat(save->port, save->slot), 0x10, 0);
    if (error != 0) {
        save->cardState = 2;
        func_001ACC38(&B_002E6550, 3);
    } else {
        save->cardState = 3;
    }
    return error;
}

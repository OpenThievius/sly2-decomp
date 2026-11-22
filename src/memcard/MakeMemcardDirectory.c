/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

#include "memcard.h"

/* The memory card manager object: lives inside SAVE at 0xFD5C. */
typedef struct B8 { char b[8]; } B8;




s32 McSync(void *, s32, s32, s32 *);                /* extern */
s32 sceMcMkdir(s32, s32, const char *);             /* extern */

s32 MakeMemcardDirectory(SAVE *save, const char *directory) {
    s32 error;

    error = McSync(&save->mc, sceMcMkdir(save->port, save->slot, directory), 0xB, 0);
    return ((error ^ 0x18) == 0) ? 0 : error;
}

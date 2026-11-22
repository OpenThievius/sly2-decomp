/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

#include "memcard.h"

/* The memory card manager object: lives inside SAVE at 0xFD5C. */
typedef struct B8 { char b[8]; } B8;




s32 McSync(void *, s32, s32, s32 *);                /* extern */
s32 sceMcClose(s32);                                /* extern */

s32 McClose(SAVE *save, s32 fd) {
    return McSync(&save->mc, sceMcClose(fd), 3, 0);
}

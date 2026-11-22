/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

#include "memcard.h"

/* The memory card manager object: lives inside SAVE at 0xFD5C. */
typedef struct B8 { char b[8]; } B8;




s32 McSync(void *, s32, s32, s32 *);                /* extern */
s32 sceMcOpen(s32, s32, const char *, s32);         /* extern */

s32 McOpenFile(SAVE *save, const char *path, s32 mode, s32 *fd) {
    return McSync(&save->mc, sceMcOpen(save->port, save->slot, path, mode), 2, fd);
}

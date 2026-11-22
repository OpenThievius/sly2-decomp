/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

#include "memcard.h"

s32 NewSema(s32, s32);                              /* extern */

void InitMemcard__FP7MEMCARD(MEMCARD *card) {
    card->semaphoreId = NewSema(1, 1);
    card->threadId = -1;
    card->busy = 0x20;
}

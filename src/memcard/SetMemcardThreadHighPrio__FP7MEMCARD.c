/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

#include "memcard.h"

s32 ChangeThreadPriority(s32, s32);                /* extern */
s32 FMemcardThreadValid__FP7MEMCARD(MEMCARD *);     /* extern */
s32 SignalSema(s32);                               /* extern */
s32 WaitSema(s32);                                 /* extern */

void SetMemcardThreadHighPrio__FP7MEMCARD(MEMCARD *card) {
    if (FMemcardThreadValid__FP7MEMCARD(card) != 0) {
        ChangeThreadPriority(card->threadId, 1);
    }
    WaitSema(card->semaphoreId);
    SignalSema(card->semaphoreId);
}

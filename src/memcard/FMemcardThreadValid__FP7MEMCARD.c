/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

#include "memcard.h"

s32 FMemcardThreadValid__FP7MEMCARD(MEMCARD *card) {
    return ~card->threadId != 0;
}

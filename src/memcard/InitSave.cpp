/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "memcard.h"
extern "C" void InitMemcard__FP7MEMCARD(MEMCARD *);
extern "C" void sceMcInit();
extern "C" void InitSave(SAVE *save, int port, int slot) {
    sceMcInit();
    InitMemcard__FP7MEMCARD(&save->mc);
    save->port = port;
    save->slot = slot;
    save->state = -1;
    save->cardState = 0;
    save->tStamp = save->tNext = 0.0f;
    save->cardType = 0;
    save->cFree = 0;
    save->formatted = 0;
}

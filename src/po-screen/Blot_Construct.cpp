// SPDX-License-Identifier: GPL-3.0-or-later
#include "blot.h"

extern "C" {
void InitSl(SL *, s32);
extern char D_002DAF30;

BLOTVIEW *Blot_Construct(BLOTVIEW *blot) {
    blot->vtable = &D_002DAF30;
    blot->cur = -1;
    unsigned index = 0;
    blot->field_0x0 = 0;
    blot->field_0x4 = 0;
    for (; index < 10U; index++)
        blot->alabel[index] = -1;
    InitSl(&blot->sl, 0x68);
    return blot;
}
}

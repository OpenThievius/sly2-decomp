// SPDX-License-Identifier: GPL-3.0-or-later
#include "blot.h"

extern "C" {
s32 FBlotLabelPlaying(BLOT *, s32);
s32 FTaskComplete(TASK *);
void UpdateBlotMovie(BLOT *);
s32 sprintf(char *, const char *, ...);
extern char D_002C3EC0[];
extern const char RO_002A8AA0[];

void JobBlot_Update(JOBBLOT *blot) {
    s32 completeB = 0;
    s32 completeA = 0;
    s32 playing = 0;
    s32 index;
    UpdateBlotMovie(blot);
    for (index = 0; index < blot->ctaskA; index++) {
        TASK *task = blot->ataskA[index].ptask;
        if (task != 0) {
            if (task->state == 1) {
                playing++;
            } else if (FTaskComplete(task) != 0) {
                completeB++;
                completeA++;
            }
        }
    }
    for (index = 0; index < blot->ctaskB; index++) {
        TASK *task = blot->ataskB[index].ptask;
        if (task != 0) {
            if (task->state == 1) {
                playing++;
            } else if (FTaskComplete(task) != 0) {
                completeB++;
            }
        }
    }
    if (FBlotLabelPlaying(blot, 0x314) != 0) {
        sprintf(D_002C3EC0, RO_002A8AA0, completeA);
        sprintf(D_002C3EC0 + 0x30, RO_002A8AA0, blot->ctaskA);
        sprintf(D_002C3EC0 + 0x60, RO_002A8AA0, blot->ctaskA - completeA);
    }
    if (completeB == blot->ctaskA + blot->ctaskB || playing == 0) {
        blot->Hide();
        return;
    }
    if (playing > 0) {
        blot->Select(-1);
    }
}
}

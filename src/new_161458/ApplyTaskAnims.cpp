// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"

extern "C" {
void func_00162250(JOB *pjob, ANIMREC *panim, s32 state, s32 fPlay);

void ApplyTaskAnims(JOB *pjob, s32 state, s32 canim, ANIMREC *aanim, s32 fPlay) {
    ANIMREC *panim;
    s32 remaining;

    if (canim > 0) {
        panim = aanim;
        remaining = canim;
        do {
            func_00162250(pjob, panim, state, fPlay);
            remaining -= 1;
            panim += 1;
        } while (remaining != 0);
    }
}

}

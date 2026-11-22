/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

void func_001A3078(void **pslot);
extern void *B_002E1E60;

void IncrementSwShowCount(struct SWVIEW *psw) {
    s32 cshow;

    cshow = psw->cshow + 1;
    psw->cshow = cshow;
    if (cshow == 1) {
        func_001A3078(&B_002E1E60);
    }
}

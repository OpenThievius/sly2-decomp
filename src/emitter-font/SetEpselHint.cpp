// SPDX-License-Identifier: GPL-3.0-or-later
#include "epsel.h"
#include "clock.h"
extern "C" {
int func_00213B00(EPSEL *, int);
void SetEpselHint(EPSEL *pepsel, s32 hint) {
    if (pepsel->hint != hint) {
        if (hint != 0) {
            if (hint == 1) {
                func_00213B00(pepsel, 0x5BD);
            }
        } else {
            func_00213B00(pepsel, 0x5BE);
        }
        pepsel->hint = hint;
        pepsel->tHint = g_2dded0.tReal;
    }
}
}

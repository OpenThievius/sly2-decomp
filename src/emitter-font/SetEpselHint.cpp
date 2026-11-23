// SPDX-License-Identifier: GPL-3.0-or-later
#include "epsel.h"
extern "C" {
int func_00213B00(EPSEL *, int);
extern f32 g_2ddf0c;
void SetEpselHint(EPSEL *pepsel, s32 hint) {
    if (*(s32 *)((char *)pepsel + 0x12C) != hint) {
        if (hint != 0) {
            if (hint == 1) {
                func_00213B00(pepsel, 0x5BD);
            }
        } else {
            func_00213B00(pepsel, 0x5BE);
        }
        *(s32 *)((char *)pepsel + 0x12C) = hint;
        pepsel->tHint = g_2ddf0c;
    }
}
}
